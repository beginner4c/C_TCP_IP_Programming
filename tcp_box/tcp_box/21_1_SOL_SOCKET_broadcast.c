#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // 옵션 설정 시 필요 헤더
#pragma comment(lib, "ws2_32.lib")

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) {
		printf("SOCKET ERROR!\n");
		return -1;
	}

	BOOL en = TRUE; // BOOL 자료형에 참을 넣어준다
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&en, sizeof(en)); // 옵션 설정
	// socket handle 값, level 값, option 이름, 옵션 사용 여부, 사용 여부의 크기
	// socket 옵션에서 broadcast 환경을 사용한다고 설정한 것

	SOCKADDR_IN serveraddr; // 주소 구조체 생성
	serveraddr.sin_addr.s_addr = inet_addr("192.168.41.255"); // ip 주소 마지막에 255 를 넣어주어야 한다
	// 그래야 broadcast 시 같은 대역대 모든 공간에 데이터를 뿌려줄 수 있기 때문이다
	serveraddr.sin_family = AF_INET; // ip version
	serveraddr.sin_port = htons(22222); // 포트 번호
}