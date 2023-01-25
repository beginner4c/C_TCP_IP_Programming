// 전처리기 선언
// server
#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int ran, cnt; // random 과 count 변수 선언
// 전역 변수는 미리 초기화 되어 0 이다

// 사용할 함수 선언
int up(int user) { // 
	int result;
	printf("updown game start\n");
	if (!ran) // ran 이 0 일 경우
		ran = rand_(); // ran 에 rand_ 함수 호출 (랜덤한 숫자 변수에 대입)
	result = check(user); // 
	return result;
}

int rand_() { // 랜덤한 하나의 수를 돌려주는 함수
	srand(time(NULL));
	return rand() % 99 + 1;
}

int check(int user) { // 받은 수와 random 한 수의 비교를 위한 함수
	printf("input : %d\n", user);
	printf("com : %d\n", ran);
	if (user > ran) { // 받은 수가 random 한 수 보다 클 때
		cnt++;
		return 1;
	}
	else if (user < ran) { // 받은 수가 random 한 수 보다 작을 때
		cnt++;
		return -1;
	}
	else { // 받은 수와 random 한 수가 같을 때
		cnt++;
		return 0;
	}
	system("pause");
	system("cls");
}

typedef struct u {
	int num;
	char str[1024];
}ST; // 클라이언트와 동일한 구조체 선언

main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // winsock dll 로드

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0); // 소켓 생성
	if (s == INVALID_SOCKET) { // 에러 발생 확인
		printf("socket error\n");
		return -1;
	}

	SOCKADDR_IN addr; // IPv4 용 주소 구조체 선언
	addr.sin_family = AF_INET; // IPv4 의 값
	addr.sin_port = htons(12345); // port 번호 저장
	addr.sin_addr.S_un.S_addr = inet_addr("172.22.200.48"); // server ip 저장
	// addr.sin_addr.s_addr = 역시 ip 저장 시 사용 가능

	int error; // error 확인 용 변수 선언
	error = bind(s, (SOCKADDR*)&addr, sizeof(addr)); // 운영체제에게 허락을 받아주는 역할
	if (error == SOCKET_ERROR) {
		printf("bind error\n");
		return -1;
	}

	error = listen(s, SOMAXCONN); // 포트를 listening 상태로 변경(대기)
	if (error == SOCKET_ERROR) { // 포트 listen 함수 실패 시 
		printf("listen error\n");
		return -1;
	}

	SOCKET CLT_s; // 전달할 때 사용할 SOCKET 선언
	SOCKADDR_IN CLT_addr; // IPv4 용 구조체 선언
	int size = sizeof(CLT_addr); // IPv4 용 구조체의 크기 저장

	CLT_s = accept(s, (SOCKADDR*)&CLT_addr, &size); // 연결 대기
	if (CLT_s == INVALID_SOCKET) { // 연결 대기 함수 실패 시
		printf("accept error\n");
		return -1;
	}

	char buf[1024];
	int len;
	int user;
	int result;
	ST st;

	while (1) {
		len = recv(CLT_s, (char*)&user, sizeof(user), 0); // client 에서 보낸 데이터 len 에 수신
		// recv 함수가 성공할 경우 user에는 client 에서 보낸 숫자가 담겨 있다
		if (len == SOCKET_ERROR) { // recv 함수 실패 시
			printf("recv error\n");
			return -1;
		}
		result = up(user); // result 에 up 함수를 통해 1 or -1 or 0 을 받아올 것
		if (result == 1) { // 수신한 데이터가 random 값 보다 작을 경우
			printf("==== UP ====\n");
			sprintf(st.str, "==== UP ====\n"); // st.str 에 문자열을 저장
			send(CLT_s, (char)&st, sizeof(st), 0); // st 구조체의 데이터를 send 함수를 통해 전달
		}
		else if (result == -1) { // 수신한 데이터가 random 값 보다 클 경우
			printf("==== DOWN ====\n");
			sprintf(st.str, "==== DOWN ====\n"); // st.str 에 문자열을 저장
			send(CLT_s, (char*)&st, sizeof(st), 0); // st 구조체의 데이터를 send 함수를 통해 전달
		}
		else { // 수신한 데이터와 random 값이 같은 경우
			printf("%d 번 만에 정답\n", cnt);
			sprintf(st.str, "%d 번 만에 정답\n\n == !! Clear !! ==\n", cnt); // st.str 에 문자열을 저장
			st.num = 1; // st.num 에 1 대입 (정답을 맞췄다는 것을 알려주기 위한 수)
			send(CLT_s, (char)&st, sizeof(st), 0); // st 구조체의 데이터를 send 함수를 통해 전달
			break; // while 문 탈출
		}
	}

	// 사용했던 소켓들 정리
	closesocket(CLT_s);
	closesocket(s);
	WSACleanup(); // dll 언로드
	
	return 0;
}