// 전처리기 구성
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>
#include<ws2tcpip.h> // 옵션 헤더

int main() {
	// dll 로드
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// socket 생성
	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) {
		printf("socket error!\n");
		return -1;
	}

	// 브로드 캐스트 활성
	BOOL opt = TRUE; // 정수형 공간 BOOL 생성
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt)); // broadcast 활성화
	// socket handle 값, level option, option 이름, 활성화 여부, 활성 여부에 대한 크기

	// 데이터 송신
	SOCKADDR_IN SRVaddr; // 서버 주소 구조체
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // 주소 구조체 초기화

	SRVaddr.sin_addr.s_addr = inet_addr("192.168.41.255"); // broadcast 를 위한 ip 주소 (class에 맞춰 255)
	SRVaddr.sin_port = htons(12345); // 사용할 포트 번호
	SRVaddr.sin_family = AF_INET; // ipv4

	char sendbuf[1024]; // 보낼 메시지를 저장할 공간
	memset(sendbuf, 0, sizeof(sendbuf)); // 저장 공간 초기화

	printf("input data : ");
	scanf("%s", sendbuf); // 보낼 메시지 입력

	int sendsize = 0; // 보낸 데이터 크기 확인용 공간
	sendsize = sendto(sock, sendbuf, strlen(sendbuf), 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // 데이터 전송
	// socket handle 값, 보낼 데이터, 보낼 데이터 크기, option, 주소 구조체, 주소 구조체 크기

	printf("송신 데이터 크기 : %d\n", sendsize); // 데이터 크기 확인

	// socket, dll 종료
	closesocket(sock);
	WSACleanup();

	return 0;
}