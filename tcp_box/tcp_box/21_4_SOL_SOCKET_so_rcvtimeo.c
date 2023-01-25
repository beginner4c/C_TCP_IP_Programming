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

	int opt = 0;
	int optlen = sizeof(opt);

	getsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&opt, &optlen);
	if (opt == 0) {
		printf("기본 값 : %d\n", opt);
	}

	opt = 3000; // 3 초

	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&opt, optlen); // recvfrom 에 timeout을 3 초 준다
	// 3초 동안 데이터가 들어오지 않으면 recvfrom 함수를 종료한다
	// socket handle 값, level option, option 이름, timeout 설정 값, 설정 값의 크기

	printf("3초 동안 데이터 수신 설정 됨 : %d\n", opt); // 설정된 값 확인

	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&opt, optlen); // sendto 에 timeout 을 3 초 준다
	// 3초 동안 데이터가 보내지지 않으면 sendto 함수를 종료한다.
}