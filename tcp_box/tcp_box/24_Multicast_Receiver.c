#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // 옵션 설정 시 필요 헤더
#pragma comment(lib, "ws2_32.lib")

// MULTICAST 통신 => 일 대 다수의 통신 방법

int main() {
	WSADATA wsa; // dll 로드
	WSAStartup(MAKEWORD(2, 2), &wsa); // 버전 확인

	// udp 소켓 생성
	SOCKET mulsock = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, udp, option
	if (mulsock == INVALID_SOCKET) { // 소켓 생성 확인
		printf("SOCKET ERROR!\n");
		return -1;
	}

	// 주소 결합
	SOCKADDR_IN srvaddr; // 주소 구조체 생성
	memset(&srvaddr, 0, sizeof(srvaddr)); // 주소 구조체 초기화
	
	srvaddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // ip 주소
	srvaddr.sin_family = AF_INET; // ip version 4
	srvaddr.sin_port = htons(12345); // port 번호

	int errch = 0; // bind error check
	errch = bind(mulsock, (SOCKADDR*)&srvaddr, sizeof(srvaddr)); // os에 허가 받음
	// socket handle 값, 주소 구조체, 주소 구조체 크기
	if (errch == SOCKET_ERROR) { // bind 함수 성공 확인
		printf("bind error\n");
		return -1;
	}

	// 멀티캐스트 가입
	struct ip_mreq MR; // 멀티캐스트 가입용 주소 구조체
	MR.imr_interface.s_addr = inet_addr("192.168.41.1"); // local 주소를 입력
	MR.imr_multiaddr.s_addr = inet_addr("224.2.2.2"); // multicast 로 받을 주소를 직접 입력

	setsockopt(mulsock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&MR, sizeof(MR)); // IP_ADD_MEMBERSHIP으로 가입
	// socket handle 값, LEVLE 값, OPTION 값, 멀티캐스트 주소 구조체, 주소 구조체 크기

	// 데이터 수신
	char recvbuf[1024]; // 데이터를 수신할 공간
	memset(recvbuf, 0, sizeof(recvbuf)); // 공간 초기화
	
	SOCKADDR_IN cltaddr; // 상대 주소를 받을 주소 구조체
	int cltlen = sizeof(cltaddr); // 주소 구조체 크기 저장
	memset(&cltaddr, 0, cltlen); // 주소 구조체 초기화

	int recvlen = 0; // 받은 데이터 크기 확인용 공간
	recvlen = recvfrom(mulsock, recvbuf, sizeof(recvbuf), 0, (SOCKADDR*)&cltaddr, &cltlen); // 데이터 수신
	// socket handle 값, 데이터 저장 공간, 저장 공간 크기, option, 저장할 주소 구조체, 주소 구조체 크기
	printf("수신 데이터 크기 : %d\n", recvlen); // recvfrom 함수를 통해 크기 확인
	printf("수신 데이터 : %s\n", recvbuf); // 받은 데이터 확인

	// 멀티캐스트 탈퇴
	setsockopt(mulsock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&MR, sizeof(MR)); // IP_DROP_MEMBERSHIP으로 탈퇴

	// socket, dll 종료
	closesocket(mulsock);
	WSACleanup();

	return 0;
}