#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

typedef struct u {
	int num;
	char str[1024];
}ST;

main() {
	// winsock dll 로드
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// ipv4 와 tcp 의 정보를 담은 소켓 생성
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("socket error\n");
		return -1;
	}

	SOCKADDR_IN addr; // SOCKADDR_IN >>> ipv4 에 맞춰진 주소와 포트를 담을 구조체 형식
	addr.sin_family = AF_INET; // ipv4 저장
	addr.sin_port = htons(12345); // 포트 번호 12345 를 host 형식에서 network 형태로
	addr.sin_addr.s_addr = inet_addr("172.22.200.48"); // 아이피 번호 저장

	// connect 함수를 통해 상대방을 찾아간다
	int error = connect(s, (struct sockaddr*)&addr, sizeof(addr));
	if (error == SOCKET_ERROR) { // connect 실패 시
		printf("connect error\n");
		return -1;
	}

	// 데이터를 보낼 변수와 구조체 선언
	char buf[500];
	int user;
	ST st;
	// 맞출 때 까지 계속 새롭게 데이터를 보낸다
	while (1) {
		memset(&st, 0, sizeof(st)); // 만들어 준 구조체 0 으로 초기화
		printf("보낼 데이터 입력 : ");
		scanf("%d", &user); // 보낼 데이터 입력
		int len = send(s, (char*)&user, sizeof(user), 0); //send 함수를 통해 서버에 입력한 데이터를 넘긴다
		// int 형태 자료는 char 형태로 casting 해서 보내야 한다
		recv(s, (char*)&st, sizeof(st), 0); // 서버에서 보낸 데이터를 st 에 저장한다
		printf("%s\n", st.str); // st 구조체의 서버에서 전달받은 str 값을 출력
		if (st.num == 1) // 정답일 경우 while 문을 빠져나간다
			break;
	}
	closesocket(s);
	WSACleanup();
	return 0;
}