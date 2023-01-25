// IPPROTO_IP를 이용해 설문조사 프로그램 작성
// sender와 receiver 따로 존재
// sender는 설문 내용의 문자열을 receiver들에게 전송
// receiver는 전송 내용을 화면에 출력 후 입력 값을 sender에게 유니캐스트 전송
// sender는 receiver들의 입력 값을 다시 출력


#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // 옵션 설정 시 필요 헤더
#pragma comment(lib, "ws2_32.lib")

// MULTICAST 통신 => 일 대 다수의 통신 방법

typedef struct msg {
	int a_num;
	char q_str[512];
}_msg;

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
	srvaddr.sin_port = htons(22222); // port 번호

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
	mr.imr_multiaddr.s_addr = inet_addr("233.3.3.3"); // multicast 로 받을 주소를 직접 입력

	setsockopt(mulsock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mr, sizeof(mr)); // IP_ADD_MEMBERSHIP으로 가입
	// socket handle 값, LEVLE 값, OPTION 값, 멀티캐스트 주소 구조체, 주소 구조체 크기

	SOCKADDR_IN recvaddr; // 상대 주소를 받을 주소 구조체
	int recvlen = sizeof(recvaddr); // 주소 구조체 크기 저장
	memset(&recvaddr, 0, recvlen); // 주소 구조체 초기화

	// 데이터 수신
	_msg msg; // 데이터 저장 구조체 선언
	memset((char*)&msg, 0, sizeof(msg)); // 구조체 초기화

	errch = recvfrom(mulsock, (char*)&msg, sizeof(msg), 0, (SOCKADDR*)&recvaddr, &recvlen); // 데이터 수신
	// socket handle 값, 데이터 저장 공간, 저장 공간 크기, option, 상대 주소 저장 구조체, 주소 구조체 크기
	if (errch == SOCKET_ERROR) { // 수신 실패 시 예외 처리
		printf("RECEIVEFROM FUNCTION ERROR\n");
		return -1;
	}

	printf("%s", msg.q_str); // 받은 데이터 출력
	printf("\n답변 입력(1-4 : "); // 출력
	int an = 0;
	scanf("%d", &an); // 데이터 입력

	memset((char*)&msg, 0, sizeof(msg)); // 데이터를 받았던 구조체 초기화
	msg.a_num = an; // 구조체에 입력된 데이터 삽입

	errch = sendto(mulsock, (char*)&msg, sizeof(msg), 0, (SOCKADDR*)&recvaddr, recvlen); // 데이터 송신
	// socket handle 값, 보낼 데이터 구조체, 구조체 크기, option, 상대방 주소 구조체, 주소 구조체 크기
	if (errch == SOCKET_ERROR) { // 전송 실패 시 예외 처리
		printf("SENDTO FUNCTION ERROR\n");
		return -1;
	}

	// 멀티캐스트 그룹 탈퇴
	setsockopt(mulsock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mr, sizeof(mr));

	// socket dll 종료
	closesocket(mulsock);
	WSACleanup();

	return 0;
}