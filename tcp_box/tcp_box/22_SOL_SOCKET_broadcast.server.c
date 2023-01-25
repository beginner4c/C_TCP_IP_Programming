// 전처리기 구성
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>
#include<ws2tcpip.h>

int main() {
	// dll 로드
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// socket 생성
	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) {
		printf("socket error!\n");
		return -1;
	}

	// 주소 결합
	// struct sockaddr_in SRVaddr;
	SOCKADDR_IN SRVaddr; // 주소 구조체 생성
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // 주소 구조체 초기화

	SRVaddr.sin_family = AF_INET; // ipv4
	SRVaddr.sin_port = htons(12345); // 사용할 포트 번호
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // 서버의 아이피 주소
	// SRVaddr.sin_addr.S_un.S_addr = 아이피 주소

	int errch = 0;
	errch = bind(sock, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind 함수를 통해 os에 허락
	if (errch == SOCKET_ERROR) { // bind error 발생 시 예외 처리
		printf("BIND ERROR\n");
		return -1;
	}

	// 데이터 수신
	char recvbuf[1024]; // 데이터를 수신할 공간
	memset(recvbuf, 0, sizeof(recvbuf)); // 수신 공간 초기화

	SOCKADDR_IN CLTaddr; // client 주소를 저장할 주소 구조체 생성
	int CLTlen = sizeof(CLTaddr); // 주소 구조체 크기 저장
	memset(&CLTaddr, 0, CLTlen); // 주소 구조체 초기화

	int recvlen = 0; // 수신한 데이터 크기를 저장할 공간
	recvlen = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, (SOCKADDR*)&CLTaddr, &CLTlen); // 데이터 수신
	// socket handle 값, 데이터 수신 공간, 수신 공간 크기, option, client 주소 구조체, 주소 구조체 크기

	printf("수신 데이터 크기 : %d\n", recvlen); // 확인용 출력문
	printf("수신 데이터 : %s\n", recvbuf);

	// socket, dll 종료
	closesocket(sock);
	WSACleanup();
	
	return 0;
}