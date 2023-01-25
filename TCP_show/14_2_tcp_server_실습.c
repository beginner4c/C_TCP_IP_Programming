// tcp서버-클라이언트 에코 서버 구현
// echo server 란?
// 클라이언트가 "hello" 라는 문자열을 송신하면 서버는
// "hello"를 수신 후 "hello" 문자열을 클라이언트에게 송신함

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main() {
	WSADATA wsa;

	// winsock dll 로드
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// 소켓 생성
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("socket error");
		return -1;
	}

	// 주소 결합
	// struct sockaddr_in
	SOCKADDR_IN SRVaddr;
	memset(&SRVaddr, 0, sizeof(SRVaddr));

	// 자기 자신에 대한 정보를 구조체에 입력해준다
	SRVaddr.sin_family = AF_INET;
	SRVaddr.sin_port = htons(12345);
	SRVaddr.sin_addr.s_addr = inet_addr("172.22.200.48");
	// SRVaddr.sin_addr.S_un.S_addr = 아이피 주소

	int errch = 0;
	errch = bind(s, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind 함수를 통해 운영체제에게 허락을 받는다
	if (errch == SOCKET_ERROR) {
		printf("bind error");
		return -1;
	}
	
	// 포트 오픈
	errch = listen(s, SOMAXCONN); // listen 함수를 통해 현재 포트를 listen 상태로 만들어준다
	if (errch == SOCKET_ERROR) {
		printf("listen error");
		return -1;
	}

	// 연결 허용
	SOCKET CLTs;
	SOCKADDR_IN CLTaddr;
	memset(&CLTaddr, 0, sizeof(CLTaddr));
	int size = sizeof(CLTaddr);

	CLTs == accept(s, (SOCKADDR*)&CLTaddr, &size); // accept 함수를 통해 상대방에게서 요청이 올 때까지 대기한다
	// 만약 상대방에게서 connect 함수를 통해 요청이 오면 accept 함수를 통해 받게 된다
	if (CLTs == INVALID_SOCKET) {
		printf("accpet error");
		return -1;
	}

	printf("[%s] : %d", inet_ntoa(CLTaddr.sin_addr), ntohs(CLTaddr.sin_port));

	// 데이터 수신 
	// client 의 send 함수를 통해 받은 데이터를 저장해야 한다
	char recvbuf[1024]; // 전달받은 데이터를 저장할 곳
	memset(recvbuf, 0, sizeof(recvbuf)); // 저장소 초기화

	int recvsize = 0; // 
	recvsize = recv(CLTs, recvbuf, sizeof(recvbuf), 0); // recvbuf 에 상대방이 보낸 메세지를 저장하고 해당 크기를 저장한다
	printf("%s\n", recvbuf);
	printf("수신 데이터 크기 : %d\n", recvsize);

	send(CLTs, recvbuf, strlen(recvbuf), 0); // 받아온 메세지를 그대로 다시 보내게 된다

	// 소켓 종료 및 dll unload
	closesocket(s);
	WSACleanup();
	return;
}