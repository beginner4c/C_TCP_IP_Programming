// IPPROTO_IP 를 이용해 시간 서버 프로그램을 작성
// Sender 와 Receiver 가 따로 존재
// Sender 는 현재 시간을 Receiver들에게 1 초 간격으로 전송
// Receiver 는 전송 내용인 현재 시간을 1 초 간격으로 출력

// Receiver 시간 서버

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
	struct ip_mreq mr; // 멀티캐스트 가입용 주소 구조체
	mr.imr_interface.s_addr = inet_addr("192.168.41.1"); // local 주소를 입력
	mr.imr_multiaddr.s_addr = inet_addr("224.2.2.2"); // multicast 로 받을 주소를 직접 입력

	setsockopt(mulsock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mr, sizeof(mr)); // IP_ADD_MEMBERSHIP으로 가입
	// socket handle 값, LEVLE 값, OPTION 값, 멀티캐스트 주소 구조체, 주소 구조체 크기

	// 데이터 수신
	char recvbuf[1024]; // 데이터를 수신할 공간
	memset(recvbuf, 0, sizeof(recvbuf)); // 공간 초기화

	SOCKADDR_IN cltaddr; // 상대 주소를 받을 주소 구조체
	int cltlen = sizeof(cltaddr); // 주소 구조체 크기 저장
	memset(&cltaddr, 0, cltlen); // 주소 구조체 초기화

	int recvlen = 0; // 받은 데이터 크기 확인용 공간

	// 수신 함수 타임아웃 설정
	int opt = 5000; // timeout 설정값 => 5 초
	setsockopt(mulsock, SOL_SOCKET, SO_RCVTIMEO, (char*)&opt, sizeof(opt)); // timout 설정
	// socket handle 값, level 값, option 값, char 형태의 설정값, 설정값 크기

	while (1) // break를 만날 때까지 반복
	{
		recvlen = recvfrom(mulsock, recvbuf, sizeof(recvbuf), 0, (SOCKADDR*)&cltaddr, &cltlen); // 데이터 수신
		// socket handle 값, 데이터 수신 공간, 수신 공간 크기, option, 수신할 주소 구조체, 주소 구조체 크기
		if (recvlen == SOCKET_ERROR) // 5 초 간 수신된 데이터가 없거나 데이터 수신 실패 시 break
			break;

		printf("수신 데이터 : %s\n", recvbuf); // 수신된 데이터 확인 출력
	}

	// 멀티캐스트 그룹 탈퇴
	setsockopt(mulsock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mr, sizeof(mr)); // IP_DROP_MEMBERSHIP -> 멀티캐스트 그룹 탈퇴
	// socket handle 값, level 값, option 값, 멀티캐스트용 주소 구조체, 주소 구조체 크기

	// socket, dll 종료
	closesocket(mulsock);
	WSACleanup();

	return 0;
}