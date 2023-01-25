// 10 부터는 단순한 text 가 아닌 file or image 를 전송한다

// tcp client 에서 보낼 data size를 알려주고,
// tcp server 는 client 가 보낼 data size 만큼
// 저장 공간을 만들어 수신하기

// tcp server 입장에서는 client 가 보낼 data size를 모르기에
// size를 전송 받아 전송받을 size 만큼 data 를 수신함

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>
#include<stdlib.h>

main(int agrc, char* argv[]) {

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
	errch = connect(s, (SOCKADDR*)&SRVAddr, sizeof(SRVAddr));
	if (errch == SOCKET_ERROR) {
		printf("connect error\n");
		return -1;
	}

	// 데이터 크기 송신
	FILE* fp; // 파일 형태의 포인터 변수 생성
	fp = fopen("C:\\Data.txt", "rb"); // rb 모드로 해당 위치의 파일을 읽어오겠다
	fseek(fp, 0, SEEK_END); // 파일이 제대로 열렸다면 fp 파일의 커서를 제일 끝으로 이동시킨다
	int fsize = ftell(fp); // 현재 파일에 대한 ftell 함수를 통해 크기를 얻어오겠다
	// ftell 함수 : 파일의 시작점부터 파일의 커서 위치까지의 크기 계산 함수 
	fclose(fp);

	send(s, (char*)&fsize, sizeof(fsize), 0); // 파일의 총 크기를 server 에 먼저 전송하겠다
	// socket handle 값, 파일에 대한 크기(char 형태만 가능)
	// 서버가 이 함수를 정상적으로 받는다면 전송받은 크기만큼 저장 공간을 확보했을 것

	// 데이터 송신
	fp = fopen("C:\\Data.txt", "rb"); // 다시 rb 모드로 해당 위치의 파일을 읽어온다
	char* sendbuf = (char*)malloc(fsize); // 동적할당을 통해 fsize 만큼 크기를 확보를 한다
	memset(sendbuf, 0, fsize); // 동적할당받은 공간을 전부 0 으로 초기화 시키겠다
	fread(sendbuf, 1, fsize, fp); // 현재 파일에 저장된 값을 1byte 씩 반복해서 sendbuf 라는 저장공간에 저장하겠다 
	fclose(fp);

	int size;
	size = send(s, sendbuf, fsize, 0); // sendbuf 속 data 를 server 측으로 보내겠다
	printf("송신 데이터 크기 : %d\n", size); // 정상적으로 보냈을 경우 size 에 보낸 데이터의 크기가 출력된다

	// 소켓 종료
	closesocket(s);

	// dll unload
	WSACleanup();

	return 0;
}