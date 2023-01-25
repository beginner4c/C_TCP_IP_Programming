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
	
	// 주소 구조체
	SOCKADDR_IN muladdr;
	memset(&muladdr, 0, sizeof(muladdr));

	muladdr.sin_addr.s_addr = inet_addr("192.168.41.1");
	muladdr.sin_family = AF_INET;
	muladdr.sin_port = htons(33333);

	int error;
	error = bind(mulsock, (SOCKADDR*)&muladdr, sizeof(muladdr));
	// bind(socket handle 값, 주소 구조체, 주소 구조체 크기)
	if (error == SOCKET_ERROR) {
		printf("bind error\n");
		return -1;
	}

	// 멀티캐스트 주소 구조체
	struct ip_mreq Mreq;
	Mreq.imr_interface.s_addr = inet_addr("192.168.41.1"); // local에 대한 주소를 담을 수 있는 공간
	Mreq.imr_multiaddr.s_addr = inet_addr("233.3.3.3"); // 멀티캐스트를 위한 주소를 담을 수 있는 공간

	// 멀티 캐스트 가입
	setsockopt(mulsock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&Mreq, sizeof(Mreq)); // IP_ADD_MEMBERSHIP = 등록
	// socket handle 값, level 값, 설정할 option 값, 등록된 주소 구조체, 주소 구조체 크기
	// setsockopt 이 끝나게 되면 Mreq.imr_multiaddr 의 값을 local 에서 받아볼 수 있게 된다

	// 데이터 수신
	char rcvbuf[512] = "\0"; // 메시지를 받을 공간
	recvfrom(mulsock, rcvbuf, sizeof(rcvbuf), 0, NULL, NULL); // 메시지 수신
	// socket handle 값, 데이터를 저장할 공간, 해당 공간의 크기, option, 주소 구조체, 주소 구조체 크기
	// recvfrom 에서 NULL 값을 사용한 이유는 이미 multicast를 가입했기 때문에 상대 주소를 안다고 판단했기 때문이다
	printf("멀티 데이터 : %s\n", rcvbuf);

	// 멀티캐스트 탈퇴 -> 가입을 했으니 일이 끝났다면 탈퇴한다
	setsockopt(mulsock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&Mreq, sizeof(Mreq)); // IP_DROP_MEMBERSHIP = 탈퇴
	// socket handle 값, level 값, 설정할 option 값, 탈퇴할 주소 구조체, 주소 구조체 크기

	closesocket(mulsock);
	WSACleanup();

	return 0;
}