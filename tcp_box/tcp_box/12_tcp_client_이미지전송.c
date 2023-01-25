// 전처리기 구성
#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main() {
	// dll 로드
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// 소켓 생성
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0); // socket 에 대한 handle 값 s
	// AF_INET = ipv4, SOCK_STREAM = TCP, protocol = null(0)
	if (s == INVALID_SOCKET) { // 소켓 생성에 실패했을 경우
		printf("socket error\n");
		return -1;
	}

	SOCKADDR_IN SRVAddr; // SOCKET 구조체 선언
	memset(&SRVAddr, 0, sizeof(SRVAddr)); // SRVAddr 을 0 으로 SRVAddr 의 크기만큼 초기화한다

	// server ip, port 정보 입력
	SRVAddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // 아이피
	SRVAddr.sin_port = htons(12345); // 포트
	SRVAddr.sin_family = AF_INET; // IPv4

	int errch = 0;
	errch = connect(s, (SOCKADDR*)&SRVAddr, sizeof(SRVAddr));
	// socket handle 값, server 의 주소 구조체 정보, 주소 구조체 크기

	if (errch == SOCKET_ERROR) {
		printf("socke error\n");
		return -1;
	}

	// 다운 파일 경로 전송
	char path[256]; // 위치 정보 저장할 배열
	memset(path, 0, sizeof(path)); // path 배열 초기화
	printf("input path : ");
	scanf("%s", path); // 경로 직접 입력 받기

	send(s, path, strlen(path), 0); // send 함수를 통해서 서버 쪽으로 경로를 보낼 것

	// 데이터 크기 수신
	int fsize = 0;
	recv(s, (char*)&fsize, sizeof(fsize), 0); // recv 함수의 형태에서는 char 형태를 넣어주어야 하기에 casting 한다
	// recv 함수를 통해서 fsize 에는 서버가 보낼 데이터 크기를 수신한다
	char* recvbuf = (char*)malloc(fsize); // heap 공간에 서버가 보낼 데이터 크기만큼 공간을 확보한다
	memset(recvbuf, 0, fsize); // 확보한 공간을 0 으로 초기화 한다

	// 데이터 수신
	recv(s, recvbuf, fsize, 0); // handle 값, 받아올 공간, 받아올 크기, 옵션 값(설정 x)

	// 파일 입출력
	FILE* fp; // 파일 입출력을 위한 fp 설정
	fp = fopen("c:\\downdData.jpg", "wb"); // 파일에 대한 위치 + 확장자를 wb 모드로 개방
	fwrite(recvbuf, 1, fsize, fp); // recvbuf 에 저장된 값을 1 byte 씩 fp 에 fsize 만큼 출력하겠다
	fclose(fp); // file 을 닫아준다 

	// 소켓 종료
	closesocket(s);

	// dll 언로드
	WSACleanup();

	return 0;
}