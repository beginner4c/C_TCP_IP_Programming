#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

// 당연히 listening 중인 server 가 없으므로 connect 단계에서 error 발생은 정당하다

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET CiTc;
	CiTc = socket(AF_INET, SOCK_STREAM, 0);

	if (CiTc == INVALID_SOCKET) {
		printf("SOCKET ERROR\n");
		return -1;
	}

	// 접속할 서버의 주소 구조체
	SOCKADDR_IN srvAddr;
	int errorCheck;
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_addr.s_addr = inet_addr("172.22.200.48");
	srvAddr.sin_port = htons(22222);
	srvAddr.sin_family = AF_INET;

	// 서버에 접속 요청
	errorCheck = connect(CiTc, (struct sockaddr*)(&srvAddr), sizeof(srvAddr));

	if (errorCheck == SOCKET_ERROR) {
		printf("CONNECT ERROR\n");
		return -1;
	}

	// 서버에 데이터 전송
	char buf[100] = "HELLO SOCKET";
	int sendSize;
	sendSize = send(CiTc, buf, sizeof(buf), 0);
	printf("%d byte 전송 완료!\n", sendSize);

	closesocket(CiTc);
	WSACleanup();
	return 0;
}