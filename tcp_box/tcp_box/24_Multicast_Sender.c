#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // 옵션 설정 시 필요 헤더
#pragma comment(lib, "ws2_32.lib")

// MULTICAST 통신 => 일 대 다수의 통신 방법

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp 소켓 생성
	SOCKET mulsock = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, socket dataGRAM, option
	if (mulsock == INVALID_SOCKET) { // 실패 시 예외 처리
		printf("SOCKET ERROR!\n");
		return -1;
	}

	// 데이터 송신
	SOCKADDR_IN srvaddr; // 주소 구조체 선언
	memset(&srvaddr, 0, sizeof(srvaddr));

	srvaddr.sin_addr.s_addr = inet_addr("224.2.2.2"); // ip address
	srvaddr.sin_port = htons(12345); // port 번호
	srvaddr.sin_family = AF_INET; // ip version

	// 멀티캐스트 TTL 값
	int multtl = 32; // 설정할 ttl 값 저장
	setsockopt(mulsock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&multtl, sizeof(multtl)); // ttl 값 설정
	// socket handle 값, level 값, option 값, char 형태 ttl 값, ttl 값 크기

	char sendbuf[1024]; // 보낼 데이터를 저장할 공간
	memset(sendbuf, 0, sizeof(sendbuf)); // 저장할 공간 0 으로 초기화

	printf("input data : "); // 출력
	scanf("%s", sendbuf); // 입력

	// 데이터 송신
	int sendsize = 0; // 보낸 데이터 크기 저장용 공간
	sendsize = sendto(mulsock, sendbuf, strlen(sendbuf), 0, (SOCKADDR*)&srvaddr, sizeof(srvaddr)); // 데이터 전송
	// socket handle 값, 보낼 데이터, 보낼 데이터 크기, option, 주소 구조체, 주소 구조체 크기 
	printf("송신 데이터 크기 : %d\n", sendsize); // 확인

	// socket, dll 종료
	closesocket(mulsock);
	WSACleanup();

	return 0;
}