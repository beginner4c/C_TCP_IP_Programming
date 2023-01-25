// tcp 클라이언트에서 파일을 하나 만들고 데이터를 넣어 저장한 후
// 파일의 내용을 읽어 tcp 서버에게 전송, 서버는 받은 데이터를 파일에 저장

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main(int agrc, char *argv[]) {

	// winsock dll load
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// 소켓 생성
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

	// 서버에 연결 요청
	int errch = 0;
	errch = connect(s,(SOCKADDR*)&SRVAddr, sizeof(SRVAddr));
	if (errch == SOCKET_ERROR) {
		printf("connect error\n");
		return -1;
	}

	// 데이터 송신
	char sendbuf[1024]; // 데이터 송신용 배열 생성
	memset(sendbuf, 0, sizeof(sendbuf)); // 해당 배열 0 으로 초기화

	FILE* fp = fopen("test.txt", "r"); // 이 c 파일이 위치한 곳에 test.txt 를 읽기로 개방하겠다 
	if (fp == NULL) { // fopen 이 실패했을 경우
		printf("파일이 없습니다");
		return -1;
	}
	// fread : 값을 얻어오고자 할때 사용하는 함수
	fread(sendbuf, 1, sizeof(sendbuf), fp); // sendbuf : 저장할 공간, 1 : 크기, count 값, 파일에 대한 정보
	// fp 라는 파일에 저장된 값을 1 byte 씩 sendbuf 크기만큼 반복해서 sendbuf라는 공간에 저장할 것이다
	// 간단하게 fp 의 내용을 sendbuf 에 가져오게 된다
	fclose(fp); // 개방했던 파일 닫아준다

	int size;
	// server에 message 를 보낼 send 함수
	size = send(s, sendbuf, sizeof(sendbuf), 0); // socket handle 값, 보낼 데이터, 보낼 데이터 크기, 옵션 값 0
	printf("송신 데이터 크기 : %d\n", size); // 보낸 데이터가 정상적이라면 출력될 것

	// 소켓 종료
	closesocket(s);

	// winsock dll unload
	WSACleanup();

	return 0;
}