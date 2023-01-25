// UDP 에코 서버 - 서버 구현

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
	char buf[1024]; // recvbuf라는 1MB 공간 생성
	memset(buf, 0, sizeof(buf)); // recvbuf 초기화

	SOCKADDR_IN CLTaddr; // 주소 구조체 변수 생상 (recvfrom 함수를 사용하기 위해)
	int CLTlen = sizeof(CLTaddr); // 주소 구조체 크기 CLTlen 에 저장
	memset(&CLTaddr, 0, CLTlen); // 주소 구조체를 0 으로 초기화

	int recvlen = 0;
	recvlen = recvfrom(s, buf, sizeof(buf), 0, (SOCKADDR*)&CLTaddr, &CLTlen);
	// recvfrom 인자값(SOCKET, 저장할 공간, 저장할 공간의 크기, 옵션 값, 클라이언트 정보 담을 구조체, 정보의 크기에 대한 주소)
	// recvlen 에는 recvfrom 을 통해 받은 데이터의 크기가 들어간다
	// recvfrom 을 통해 buf 에는 받은 데이터가 저장되고 CLTaddr 에는 클라이언트의 정보가 저장된다
	printf("수신데이터 : %s\n", buf); // 받은 데이터 확인

	printf("데이터 입력 : "); // 다시 클라이언트에 보낼 데이터
	gets_s(buf, sizeof(buf));
	sendto(s, buf, strlen(buf), 0, (SOCKADDR*)&CLTaddr, sizeof(CLTaddr));

	// 소켓 종료 및 dll 언로드
	closesocket(s);
	WSACleanup();

	return 0;
}