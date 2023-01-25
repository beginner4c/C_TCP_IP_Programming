/*
udp 이미지 파일 다운로드
클라이언트가 경로를 전송하면 서버는 수신받은 경로를 통해서
이미지 파일을 읽어 클라이언트에게 송신
클라이언트는 수신받은 파일을 이미지 파일로 저장
*/

// 전처리기 구성
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>

int main() {
	// dll 로드
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // define 된 값 MAKEWORD 를 통해 버전 정보를 wsa 에 넣어준다

	// socket 생성
	SOCKET for_send; // socket for_send 생성
	for_send = socket(AF_INET, SOCK_DGRAM, 0); // socket에 ipv4, ip protocol, option 넣어줌
	if (for_send == INVALID_SOCKET) { // socket 생성 에러 시 예외 처리
		printf("socket error\n");
		return -1;
	}

	// 데이터 송신
	SOCKADDR_IN SRVaddr; // 서버에 대한 주소 구조체 생성
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // 주소 구조체 초기화

	SRVaddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // 서버의 ip 주소
	SRVaddr.sin_port = htons(22222); // 서버와 통신할 포트 번호
	SRVaddr.sin_family = AF_INET; // 서버와 통신할 ipv

	// 경로 전송
	char path[256]; // 보낼 경로 정보를 담을 배열
	memset(path, 0, sizeof(path)); // 배열 초기화
	printf("input path : "); 
	scanf("%s", path); // 보낼 경로 정보를 입력
	sendto(for_send, path, sizeof(path), 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // 위치 정보를 서버로 송신
	// socket handle 값, 보낼 데이터, 보낼 데이터 크기, option, 서버의 주소 구조체, 주소 구조체 크기

	SOCKADDR_IN recvaddr; // 서버의 정보를 수신할 주소 구조체
	memset((char*)&recvaddr, 0, sizeof(recvaddr)); // 주소 구조체 초기화
	int recvlen = sizeof(recvaddr); // 주소 구조체 크기 저장

	// 데이터 수신
	int datasize = 0; // 파일에 대한 크기를 저장할 장소
	recvfrom(for_send, (char*)&datasize, sizeof(datasize), 0, (SOCKADDR*)&recvaddr, &recvlen); // 서버로부터 크기 수신
	// socket handle 값, 데이터를 받을 장소, 장소의 크기, option, 서버의 주소 구조체, 주소 구조체 크기
	printf("datasize : %d\n", datasize); // 파일에 대한 크기 확인
	char* recvbuf = (char*)malloc(datasize); // 파일에 대한 데이터를 저장할 공간 동적 할당
	memset(recvbuf, 0, datasize); // 동적할당 공간 초기화

	// 대용량 파일용 반복문 구성
	char buf[1024]; // 반복해서 저장할 배열 생성
	memset(buf, 0, sizeof(buf)); // 배열 초기화
	int totalbuf = 0; // 수신한 데이터 전체 크기
	int recvsize = 0; // 수신한 데이터 크기

	while (1) { // break 만날 때까지 반복
		recvsize = recvfrom(for_send, buf, sizeof(buf), 0, (SOCKADDR*)&recvaddr, &recvlen); // 서버로부터 데이터 수신
		// recvsize에는 수신한 buf 의 크기가 저장된다
		if (recvsize == 0) // 수신한 크기가 0 일 때 break
			break;
		printf("수신 : %d\n", recvsize); // 수신한 데이터 크기 확인
		memcpy(&recvbuf[totalbuf], buf, recvsize); // 수신한 데이터를 recvbuf 에 수신한 크기 만큼 복사
		totalbuf += recvsize; // 수신한 데이터 전체 크기에 수신한 데이터 크기 더해줌
	}

	// 수신한 데이터를 파일로 저장
	FILE* fp; // FILE 생성
	fp = fopen("C:\\Users\\asus\\Downloads\\udp_down_test2.png", "wb"); // 파일 위치 지정, 쓰기 모드
	fwrite(recvbuf, datasize, 1, fp); // recvbuf의 데이터를 datasize 만큼 한 번 반복해서 fp 에 저장한다
	fclose(fp); // 파일 종료

	// socket, dll 종료
	closesocket(for_send);
	WSACleanup();

	return 0;
}