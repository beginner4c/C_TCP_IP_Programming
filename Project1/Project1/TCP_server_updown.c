#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<winsock2.h>

int ran, cntl; // random and count global value

int up(int user) {
	int result;
	printf("updown game start\n");
	if (!ran) // if ran value is zero
		ran = rand_(); // insert random number (1 ~ 100)
	result = check(user);
	return result;
}

main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("socket error\n");
		return -1;
	}
}