// tcp서버-클라이언트 에코 서버 구현
// echo server 란?
// 클라이언트가 "hello" 라는 문자열을 송신하면 서버는
// "hello"를 수신 후 "hello" 문자열을 클라이언트에게 송신함

#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main(int argc, char * argv[]) {
	// dll 로드
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // 클라이언트에서 소켓 함수 사용 가능하게 만들어준다

	// 소켓 생성
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("socket error\n");
		return -1;
	}

	SOCKADDR_IN SRVAddr; // 주소 구조체 변수
	// 상대방(서버)의 정보를 전부 대입 받는다
	memset(&SRVAddr, 0, sizeof(SRVAddr)); // 주소 구조체를 초기화 한다

	// 서버 아이피와 포트 주소 정보 입력
	SRVAddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // 서버에 대한 ip 주소
	SRVAddr.sin_port = htons(12345); // 서버에 대한 port number
	SRVAddr.sin_family = AF_INET; // 서버에 대한 방식

	int errch = 0;
	errch = connect(s, (SOCKADDR*)&SRVAddr, sizeof(SRVAddr)); // connect 함수를 통해 서버측에게 연결을 시도한다
	if (errch == SOCKET_ERROR) {
		printf("connect error\n");
		return -1;
	}

	// 데이터 송신
	// client 측에서 먼저 보내기 때문에 먼저 생성해준다
	char sendbuf[1024]; // 메시지를 보낼 배열 생성
	memset(sendbuf, 0, sizeof(sendbuf)); // 해당 배열을 0 으로 초기화 시켜준다

	printf("data input : ");
	scanf("%s", sendbuf); // sendbuf 에 보낼 문자열을 저장한다 

	int size;
	size = send(s, sendbuf, strlen(sendbuf), 0); // 소켓에 대한 핸들값, client 가 보낼 data, cliet 보낼 data의 길이값
	printf("송신 데이터 크기 : %d\n", size); // send 라는 함수가 성공하게 되면 우리가 보낸 data 의 크기가 되돌아오게 된다

	// TCP 통신은 양방향 인증 통신이기 때문에 메시지를 보낸 다음에는 똑같이 되돌아오게 된다
	// 서버와의 통신이 제대로 이루어졌다면 서버에서 동일한 메시지를 되돌려주게 된다
	// 따라서, recv 용 문자열을 send 용 문자열과 동일하게 만들어주어야 한다

	char recvbuf[1024];
	memset(recvbuf, 0, sizeof(recvbuf)); // recv 용 문자열 초기화
	recv(s, recvbuf, sizeof(recvbuf), 0); // recv : data 를 받는 함수
	// recvbuf 에 recv 함수를 통해 받은 데이터를 저장하게 된다
	printf("수신 데이터 : %s\n", recvbuf); // 우리가 송신받은 데이터를 한 번 확인하는 과정
	// 보냈던 데이터가 동일하게 돌아오는게 정상이다

	// 소켓 종료
	closesocket(s);

	// dll unload
	WSACleanup();

	return 0;
}