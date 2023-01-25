// 10 부터는 단순한 text 가 아닌 file or image 를 전송한다

// tcp client 에서 보낼 data size를 알려주고,
// tcp server 는 client 가 보낼 data size 만큼
// 저장 공간을 만들어 수신하기

// tcp server 입장에서는 client 가 보낼 data size를 모르기에
// size를 전송 받아 전송받을 size 만큼 data 를 수신함

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

	// 데이터 크기 수신
	int fsize = 0;
	recv(CLTs, (char*)&fsize, sizeof(fsize), 0); // recv 함수를 통해 client 에서 날아온 크기가 fsize 에 저장된다

	// 데이터 수신
	char* recvbuf = (char*)malloc(fsize + 1); // 받아온 크기를 통해 저장공간을 동적할당해서 확보하게 된다
	// fsize + 1 인 이유는 마지막 공간에 NULL 값을 저장하기 위해서이다
	memset(recvbuf, 0, fsize + 1); // 동적할당된 공간을 전부 0 으로 초기화 한다

	recv(CLTs, recvbuf, fsize, 0); // 상대방으로 부터 날아온 message 를 수신한다
	printf("수신 데이터 : %s\n", recvbuf); // 받아온 data 확인

	FILE* fp; // FILE 형태의 포인터 변수
	fp = fopen("DownData.txt", "ab"); // ab 모드(append binary)로 해당 파일을 개방하게 된다 == fp 에 파일의 값들이 저장된다
	fwrite(recvbuf, 1, fsize, fp); // 받아온 데이터를 1 byte 씩 fsize 만큼 반복해서 fp 에 적어준다 (DownData.txt 에 저장)
	fclose(fp); // 개방한 공간을 닫는다

	// 소켓 종료 및 dll unload
	closesocket(CLTs);
	closesocket(s);
	WSACleanup();

	return 0;
}