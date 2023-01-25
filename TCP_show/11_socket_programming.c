#pragma comment(lib, "ws2_32")
#include<winsock2.h>

int main() {
	WSADATA wsa; // WSADATA 형 변수 wsa 선언
	WSAStartup(MAKEWORD(2, 2), &wsa); // 함수에 2.2 버전과 wsa 주소를 넘겨준다
	// 이 아래부터 socket 함수 사용 가능

	SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0); // SOCKET 자료형의 변수 선언
	// ipv4 와 tcp, null 값을 넣어 socket 함수 작동

	if (tcp_sock == INVALID_SOCKET) { // socket 함수가 제대로 못 만들었을 경우
		printf("소켓 에러 발생");
		return 0;
	}

	printf("소켓 성공"); // socket 함수가 제대로 작동했을 경우
	closesocket(tcp_sock); // tcp_sock socket 을 닫아준다

	WSACleanup(); // dll load 에서 unload 로 변경
	return 0;
}