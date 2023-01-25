// tcp 클라이언트에서 파일을 하나 만들고 데이터를 넣어 저장한 후
// 파일의 내용을 읽어 tcp 서버에게 전송, 서버는 받은 데이터를 파일에 저장

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main(int argc, char argv[]) {
	// winsock dll load
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// socket 생성
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("socket error\n");
		return -1;
	}

	SOCKADDR_IN SRVAddr;
	memset(&SRVAddr, 0, sizeof(SRVAddr));

	// server ip, port number 입력
	SRVAddr.sin_addr.s_addr = inet_addr("172.22.200.48");
	SRVAddr.sin_port = htons(12345);
	SRVAddr.sin_family = AF_INET;

	// bind 함수를 통해 운영체제에게 허락 받기
	int errch = 0;
	errch = bind(s, (SOCKADDR*)&SRVAddr, sizeof(SRVAddr)); // bind 함수를 통해 운영체제에게 허락을 받는다
	if (errch == SOCKET_ERROR) {
		printf("bind error");
		return -1;
	}

	// listen 함수를 통해 해당 포트를 listen 상태로 변경
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

	// accept 상태로 client 의 connect 를 기다린다
	CLTs = accept(s, (SOCKADDR*)&CLTaddr, &size); // accept 함수 호출
	if (CLTs == INVALID_SOCKET) {
		printf("accept error\n");
		return -1;
	}

	// 데이터 수신
	char recvbuf[1024]; // 수신한 데이터 저장할 공간
	memset(recvbuf, 0, sizeof(recvbuf)); // 해당 데이터 초기화

	recv(CLTs, recvbuf, sizeof(recvbuf), 0); // 소켓에 대한 핸들값, 데이터 저장할 공간, 공간에 대한 크기, 옵션값
	// recv 가 성공하면 recvbuf 에 데이터가 저장된다

	FILE* fp = fopen("data.txt", "w"); // fp 를 해당 위치의 data.txt 를 쓰기 모드로 개방한다
	fwrite(recvbuf, 1, sizeof(recvbuf), fp); // recvbuf 에 있는 데이터를 1 byte 씩 recvbuf 크기만큼 반복해서 fp 에 적어준다

	fclose(fp);

	// socket 종료 및 winsock dll unload
	closesocket(s);
	WSACleanup();

	return 0;
}