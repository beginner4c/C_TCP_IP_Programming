#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // 옵션 설정 시 필요 헤더
#pragma comment(lib, "ws2_32.lib")

// SO_RCVBUF 사용 예제 2
// 현재 버퍼의 크기를 바꿔보는 예제

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, udp, option 0
	if (sock == INVALID_SOCKET) {
		printf("SOCKET ERROR!\n");
		return -1;
	}

	int rcvbufsize = 0; // 현재 설정된 값을 얻어올 공간
	int rcvbufsizelen = sizeof(rcvbufsize); // 공간의 크기

	getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvbufsize, &rcvbufsizelen); // 현재 설정된 값을 얻어와 확인한다
	// socket handle 값, level option, option 이름, 사용할 저장 공간, 저장 공간 크기에 대한 주소

	printf("수신 버퍼 %d\n", rcvbufsize); // 수신한 버퍼 크기 확인

	rcvbufsize *= 2; // 수신한 버퍼 크기 두배 증가

	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&rcvbufsize, rcvbufsizelen);
	// socket handle 값, level option, option 이름, 사용할 저장 공간, 저장 공간 크기에 대한 주소

	printf("수신 버퍼 업데이트 : %d\n", rcvbufsize); // 두배로 증가된 값 출력 확인
}