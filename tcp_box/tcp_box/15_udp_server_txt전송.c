/*UDP 클라이언트에서 파일을 하나 만들고 데이터를 넣어
저장한 후 파일의 내용을 읽어 UDP 서버에게 전송,
서버는 받은 데이터를 파일에 저장한다*/

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

int main() {
	WSADATA wsa;
	// winsock dll 로드
	WSAStartup(MAKEWORD(2, 2), &wsa);
	
	// 소켓 생성
	SOCKET s;
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET) { // 소켓 생성 실패 시 예외 처리
		printf("socket error!\n");
		return -1;
	}

	// 주소 결합
	// struct sockaddr_in
	SOCKADDR_IN SRVaddr; // 주소 구조체 변수 생성
	memset(&SRVaddr, 0, sizeof(SRVaddr));

	SRVaddr.sin_family = AF_INET; // ipv4 사용
	SRVaddr.sin_port = htons(12345); // 포트 번호 입력
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.1.1"); // server 에 대한 ip 주소
	// SRVaddr.sin_addr.S_un.S_addr = 서버 아이피주소;

	int errch = 0;
	errch = bind(s, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind 함수를 통해 os에 허락받는다
	if (errch == SOCKET_ERROR) { // bind 실패 시 예외 처리
		printf("bind error!\n"); // 보통 서버 아이피를 잘못 넣을 경우 발생한다
		return -1;
	}
	
	// 데이터 수신
	char recvbuf[1024]; // recvbuf라는 1KB 공간 생성
	memset(recvbuf, 0, sizeof(recvbuf)); // recvbuf 초기화

	SOCKADDR_IN CLTaddr; // 주소 구조체 변수 생상 (recvfrom 함수를 사용하기 위해)
	int CLTlen = sizeof(CLTaddr); // 주소 구조체 크기 CLTlen 에 저장
	memset(&CLTaddr, 0, CLTlen); // 주소 구조체를 0 으로 초기화

	int recvlen = 0;
	recvlen = recvfrom(s, recvbuf, sizeof(recvbuf), 0, (SOCKADDR*)&CLTaddr, &CLTlen);
	// recvfrom 인자값(SOCKET, 저장할 공간, 저장할 공간의 크기, 옵션 값, 클라이언트 정보, 정보의 크기에 대한 주소)
	// recvlen 에는 recvfrom 을 통해 받은 데이터의 크기가 들어간다
	// recvfrom 을 통해 recvbuf 에는 받은 데이터가 저장된다

	/*
	printf("[%s:%d]", inet_ntoa(CLTaddr.sin_addr), ntohs(CLTaddr.sin_port)); 
	printf("%s\n", recvbuf);
	*/

	FILE* fp;
	fp = fopen("C:\\Users\\asus\\Downloads\\DownData.txt", "wb"); // rb와 다르게 wb는 없어도 생성된다
	fwrite(recvbuf, 1, recvlen, fp); // recvbuf 의 데이터를 1byte 씩 recvlen 크기 만큼 fp 에 쓴다
	fclose(fp);

	// 소켓 종료 및 dll 언로드
	closesocket(s);
	WSACleanup();
	
	return 0;
}