// 이미지를 전송해보자
// tcp server-client image file 전송
// C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\그림 샘플\

// tcp client 에서 image file 을 읽어
// tcp size 와 data 를 server 에게 송신

// tcp server는 클라이언트가 보낸 data를 수신하여 C:\ 에 저장
// 결과는 client 가 보낸 이미지 파일을 TCP 서버에서 볼 수 있음

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

	// client 와 마찬가지로 accept 함수까지는 별 다른 이유 없이 동일하다

	// 데이터 크기 수신	
	int fsize = 0;
	recv(CLTs, (char*)&fsize, sizeof(fsize), 0); // client 에서 보낸 데이터 크기를 fsize 에 수신한다

	// 데이터 수신
	char* recvbuf = (char*)malloc(fsize); // 받은 데이터 크기만큼 동적할당을 해 저장공간을 확보한다
	memset(recvbuf, 0, fsize); // 동적할당된 저장공간을 초기화 시켜주겠다

	int recvsize = 0; 
	recvsize = recv(CLTs, recvbuf, fsize, 0); // client 가 보낸 데이터를 미리 동적할당한 저장공간에 저장하겠다
	printf("수신 데이터 크기 : %d\n", recvsize); // 수신받은 데이터 크기를 확인

	FILE* fp; // FILE 형태의 포인터 변수 선언
	fp = fopen("C\\겨울.jpg", "wb"); // 파일을 쓰기 형태로 개방하겠다
	fwrite(recvbuf, 1, fsize, fp); // recvbuf 에 저장된 데이터들을 fp 위치에 전부 출력해주겠다
	fclose(fp);

	// 소켓 종료 및 dll unload
	closesocket(s);
	closesocket(CLTs);
	WSACleanup();

	return 0;
}