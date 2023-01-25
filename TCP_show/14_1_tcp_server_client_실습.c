// tcp 서버에서 접속한 클라이언트의 ip/port 주소를 출력하시오
#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa); // 소켓에 관한 함수를 사용할 수 있게 만들어준다
	
	SOCKET s;
	s = socket(AF_INET,SOCK_STREAM, 0); // 소켓 생성

	if (s == INVALID_SOCKET) {
		printf("socket_error");
		return -1;
	}

	// 주소를 대입 받는 과정 
	SOCKADDR_IN ser_addr;
	ser_addr.sin_addr.s_addr = inet_addr("172.22.200.48");
	ser_addr.sin_port = htons(12345);
	ser_addr.sin_family = AF_INET;
	// 주소를 대입 받는 과정


	int error = 0;
	error = bind(s, (struct sockaddr*)&ser_addr, sizeof(ser_addr)); // bind 함수를 통해 운영체제에게 허락을 받는다
	if (error == SOCKET_ERROR) {
		printf("bind error");
		return -1;
	}

	error = listen(s, SOMAXCONN); // 현재 등록한 포트를 listen 함수를 통해 listen 상태로 만들어준다
	if (error == SOCKET_ERROR) {
		printf("listen_error");
		return -1;
	}

	SOCKET clt_s;
	SOCKADDR_IN clt_addr;
	int size = sizeof(clt_addr);
	clt_s = accept(s, (struct sockaddr*)&clt_addr, &size); // s 라는 socket 핸들값, 상대방에게서 요청이 들어오면 clt_addr에 정보가 들어간다
	// clt_addr 에는 client 의 정보가 들어있는 것이다
	if (clt_s == INVALID_SOCKET) {
		printf("clt socket error");
		return -1;
	}

	int len;
	char buf[512];
	// len = recv(clt_s, buf, sizeof(buf), 0); // 상대방에게서 메세지가 들어오게 하는 함수
	// 이 문제에서는 client 의 ip 와 port 번호만 필요하기 때문에 필요없는 함수에 해당한다

	// clt_addr 가 모든 정보를 가지고 있다
	printf("client_port : %d\n", ntohs(clt_addr.sin_port)); // clt_addr 안의 포트 번호가 네트워크 방식으로 저장되어 있기에 호스트 방식으로 변환해서 출력한다
	// ntohs : network to host(short)
	printf("client_ip : %s\n", inet_ntoa(clt_addr.sin_addr)); // clt_addr 안의 ip 가 unsigned 형태로 저장되어 있기 때문에 문자열로 바꾸어 준다
	// inet_ntoa : network to ASCII
	closesocket(s);
	WSACleanup();
	return -1;
}