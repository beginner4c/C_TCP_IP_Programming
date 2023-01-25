// tcp 클라이언트는 실행파일 시 메인 함수의 argument를 이용하여
// tcp 서버의 ip/port 주소를 입력하여 위 프로그램을 수행하게 변경하기

#pragma comment(lib, "ws2_32.lib")
#include<WinSock2.h>
#include<stdio.h>

main(int argc, char* argv[]) {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // 소켓 함수 사용 준비 (winsock.dll load)

	SOCKET s; // SOCKET 생성
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("socket_error");
		return -1;
	}

	SOCKADDR_IN ser_addr; // 상대방(서버)에 대한 정보를 입력할 구조체
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]); // argv 배열을 통해 상대방에 접속하게 된다
	// argv 1 번 공간에 ip address 를 저장하겠다
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(atoi(argv[2])); // argv 2 번 공간에 상대방의 port number 를 저장하겠다
	// 문자열 형태로 입력받았기 때문에 2byte 정수형으로 고쳐주는 것이 atoi (a to int) 함수 이다

	int error = 0;
	error = connect(s, (struct sockaddr*) & ser_addr, sizeof(ser_addr));
	if (error == SOCKET_ERROR) {
		printf("connect_error");
		return -1;
	}

	int len = 0;
	char buf[100] = "Hello";
	len = send(s, buf, sizeof(buf), 0);

	closesocket(s);
	WSACleanup();

	return 0;
}