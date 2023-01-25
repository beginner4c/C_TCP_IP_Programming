#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // 옵션 설정 시 필요 헤더
#pragma comment(lib, "ws2_32.lib")

// MULTICAST 통신 => 일 대 다수의 통신 방법

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp 소켓 생성
	SOCKET mulsock = socket(AF_INET, SOCK_DGRAM, 0);
	if (mulsock == INVALID_SOCKET) {
		printf("SOCKET ERROR!\n");
		return -1;
	}
	// 멀티캐스트 TTL 옵션 설정
	int multtl = 64; // TTL 값 64
	setsockopt(mulsock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&multtl, sizeof(multtl));
	// setsockopt 로 옵션값 설정
	// socket handle 값, LEVEL 값, OPTION, 멀티캐스트에 대한 TTL값, 멀티캐스트에 대한 크기

	// 주소 구조체
	SOCKADDR_IN muladdr;
	memset(&muladdr, 0, sizeof(muladdr));
	muladdr.sin_addr.s_addr = inet_addr("233.3.3.3");
	muladdr.sin_family = AF_INET;
	muladdr.sin_port = htons(33333);

	// 데이터 전송
	char mulbuf[512] = "hello multicast";
	
	sendto(mulsock, mulbuf, sizeof(mulbuf), 0, (SOCKADDR*)&muladdr, sizeof(muladdr));
	// socket handle 값, char 형태의 저장 공간, 저장 공간 크기, option, 주소 구조체, 주소 구조체 크기

	// 소켓 종료
	closesocket(mulsock);
	WSACleanup();

	return 0;
}