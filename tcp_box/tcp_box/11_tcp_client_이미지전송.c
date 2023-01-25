// 이미지를 전송해보자
// 클라이언트에서 서버로 이미지 전송
// tcp server-client image file 전송
// C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\그림 샘플\

// tcp client 에서 image file 을 읽어
// tcp size 와 data 를 server 에게 송신

// tcp server는 클라이언트가 보낸 data를 수신하여 C:\ 에 저장
// 결과는 client 가 보낸 이미지 파일을 TCP 서버에서 볼 수 있음

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

	// connect 까지는 일반 client 파일과 다르지 않다

	// 역시 데이터를 주고 받을 때와 다르지 않지만 파일 명만 jpg 로 추가된 것
	// 데이터 크기 송신
	FILE* fp;
	fp = fopen("C:\\겨울.jpg", "rb"); // 겨울.jpg 를 rb 모드(읽기)로 개방하겠다
	fseek(fp, 0, SEEK_END); // fp 라는 파일의 커서를 제일 끝으로 이동
	int fsize = ftell(fp); // ftell 함수를 통해 처음부터 끝까지 크기를 구할 수 있다
	fclose(fp);

	send(s, (char*)&fsize, sizeof(fsize), 0); // ftell 을 통해 구해진 크기를 전송하게 된다
	// socket handle 값, (down casting)구해진 크기, 크기, 옵션 값 0

	// 데이터 송신
	fp = fopen("C:\\겨울.jpg", "rb"); // 겨울.jpg 를 다시 한 번 읽어와 개방하겠다
	char* sendbuf = (char*)malloc(fsize); // 받아온 크기를 통해 heap 영역에 저장 공간을 확보하겠다
	memset(sendbuf, 0, fsize); // memset 을 통해 sendbuf 를 초기화 시켜준다
	fread(sendbuf, 1, fsize, fp); // fp 의 내용을 sendbuf 라는 공간에 1 byte 씩 받아온 크기만큼 반복해 적어준다
	fclose(fp); // 개방한 파일을 다시 닫는다
	// 일반적인 파일 주고 받을 때와 똑같다

	int size;
	size = send(s, sendbuf, fsize, 0); // sendbuf 에 저장된 내용을 server에 보내겠다
	printf("송신 데이터 크기 : %d\n", size); // 정상적으로 송신되었다면 크기가 다시 돌아온다

	// 소켓 종료
	closesocket(s);

	// dll unload
	WSACleanup();

	return 0;
}