// 서버에서 클라이언트로 이미지 전송

#pragma comment(lib,"ws2_32.lib")
#include<WinSock2.h>
#include<stdio.h>

main() {
	WSADATA wsa;

	// winsock dll load
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// 소켓 생성
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	// AF_INET = ipv4, SOCK_STREAM = TCP, protocol = null(0)
	if (s == INVALID_SOCKET) {
		printf("socket error\n");
		return -1;
	}

	// 주소 결합
	// sturct sockaddr_in
	SOCKADDR_IN SRVaddr; // 주소 정보 저장을 위한 구조체 선언
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // 구조체 0 으로 초기화

	SRVaddr.sin_family = AF_INET; // IPv4
	SRVaddr.sin_port = htons(12345); // host to network short 12345 (12345 를 호스트에서 네트워크 방식으로)
	SRVaddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // ip 주소 입력
	// SRVddr.sin_addr.S_un.S_addr = 아이피 주소 

	int errch = 0; // 에러 체크를 위한 변수
	errch = bind(s, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind 함수를 통해 운영체제에 허락을 받아준다
	if (errch == SOCKET_ERROR) {
		printf("bind error\n");
		return -1;
	}

	// 포트 오픈
	errch = listen(s, SOMAXCONN); // listen 함수를 통해 포트를 listen 상태로 열어준다
	if (errch == SOCKET_ERROR) {
		printf("listen error\n");
		return -1;
	}

	// 연결 허용
	SOCKET CLTs; // 소켓 구조체 CLTs 구조체 선언
	SOCKADDR_IN CLTaddr; // ip 와 port 를 넘겨줄 구조체 선언 (IPv4에 맞춰진 구조체)
	memset(&CLTaddr, 0, sizeof(CLTaddr)); // CLTaddr 구조체 초기화
	int size = sizeof(CLTaddr); // CLTaddr 구조체 크기를 size에 담았다

	CLTs = accept(s, (SOCKADDR*)&CLTaddr, &size); // accept 함수를 통해 상대방에게서 요청이 들어오면 수락하게 된다
	if (CLTs == INVALID_SOCKET) {
		printf("accept error\n");
		return -1;
	}

	// 경로 수신
	char path[256]; // 경로를 받을 배열 선언
	memset(path, 0, sizeof(path)); // 배열 초기화
	recv(CLTs, path, sizeof(path), 0); // recv 함수를 통해 client 에서 보낸 위치 정보를 path 에 저장

	// 파일 크기 송신
	FILE* fp; // FILE 구조체 fp 선언 
	fp = fopen(path, "rb"); // fp 에 path 배열의 값을 넣어준다, 모드는 rb(읽기 모드)
	fseek(fp, 0, SEEK_END); // fp 커서 위치를 0 에서 파일의 제일 끝으로 이동시킨다
	// fseek 로 파일의 커서 위치 조정 가능
	int fsize = ftell(fp); // ftell 을 통해 fp 커서 위치까지의 크기를 fsize 에 저장한다
	// client 에서는 fsize 의 크기를 토대로 파일을 받을 준비를 할 수 있다

	send(CLTs, (char*)&fsize, sizeof(fsize), 0); // send 함수를 통해 파일의 크기를 전달한다
	// 여기까지 진행되면 client 측에서는 해당 공간을 만들고 다음 함수를 기다린다

	// 파일 데이터 송신
	char* sendbuf = (char*)malloc(fsize); // fsize 만큼 공간 확보
	memset(sendbuf, 0, fsize); // 확보한 공간을 0으로 초기화

	fseek(fp, 0, SEEK_SET); // fp 파일의 커서 위치를 가장 앞으로 위치한다
	fread(sendbuf, 1, fsize, fp); // sendbuf 공간에 1byte 만큼 fsize 만큼 fp 에서 가져온다
	fclose(fp);

	send(CLTs, sendbuf, fsize, 0); // 저장된 정보를 client 에 send 함수를 통해 전달한다

	// 소켓 종료 및 dll 언로드
	closesocket(CLTs);
	closesocket(s);
	WSACleanup();

	return 0;
}