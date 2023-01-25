#pragma comment(lib, "ws2_32")
#include<winsock2.h>
#include<stdio.h>

int main() {
	WSADATA wsa; // WSADATA 는 구조체형 자료형
	// WSADATA 구조체 wsa 선언
	WSAStartup(MAKEWORD(2, 2), &wsa); // 최초로 dll 초기화 작업
	// MAKEWORD 라는 define 된 값으로 우리가 사용할 버전을 넘겨준다
	// wsa 라는 변수에 값을 알아서 전달해주게 된다

	printf("winsock start");

	WSACleanup(); // dll load 작업을 다시 unload 시켜준다

	return 0;
}