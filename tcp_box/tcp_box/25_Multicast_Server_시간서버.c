// IPPROTO_IP 를 이용해 시간 서버 프로그램을 작성
// Sender 와 Receiver 가 따로 존재
// Sender 는 현재 시간을 Receiver들에게 1 초 간격으로 전송
// Receiver 는 전송 내용인 현재 시간을 1 초 간격으로 출력

// Sender 시간 서버

#include<winsock2.h>
#include<stdio.h>
#include<time.h>
#include<ws2tcpip.h> // 옵션 설정 시 필요 헤더
#pragma comment(lib, "ws2_32.lib")

// MULTICAST 통신 => 일 대 다수의 통신 방법

int main() {

	// dll 로드
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp 소켓 생성
	SOCKET mulsock = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, socket dataGRAM, option
	if (mulsock == INVALID_SOCKET) { // 실패 시 예외 처리
		printf("SOCKET ERROR!\n");
		return -1;
	}

	// 멀티캐스트 TTL 값
	int multtl = 64; // 설정할 ttl 값 저장
	setsockopt(mulsock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&multtl, sizeof(multtl)); // ttl 값 설정
	// socket handle 값, level 값, option 값, char 형태 ttl 값, ttl 값 크기

	// 데이터 송신
	SOCKADDR_IN srvaddr; // 주소 구조체 선언
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_addr.s_addr = inet_addr("233.3.3.3"); // ip address
	srvaddr.sin_port = htons(12345); // port 번호
	srvaddr.sin_family = AF_INET; // ip version 4

	char sendbuf[1024]; // 보낼 데이터를 저장할 공간
	memset(sendbuf, 0, sizeof(sendbuf)); // 저장할 공간 0 으로 초기화
	time_t tm; // 시간을 얻어올 구조체 생성
	struct tm* lt; // localtime 을 전달하기 위해 구조체 생성
	int sendsize = 0; // sendto 함수를 사용해 보낸 데이터 크기를 확인할 변수 선언
	int i = 0; // while 문에 사용될 조건용 변수

	while (i < 10) { // i 가 10 보다 작은 동안 반복
		time(&tm); // time 함수가 만들어졌을 때 부터 현재의 초 단위로 tm에 저장
		lt = localtime(&tm); // localtime 함수를 통해 초 단위의 시간을 년월일시분초 로 변환했다
		sprintf(sendbuf, "%d년 %d월 %d일 %d시 %d분 %d초\n",
			lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
		// sendbuf 공간에 데이터를 저장한다
		sendto(mulsock, sendbuf, strlen(sendbuf), 0, (SOCKADDR*)&srvaddr, sizeof(srvaddr)); // 데이터 전송
		printf("%d번 전송\n", i + 1); // 전송된 횟수 확인
		i++; // 조건용 i 증가
		Sleep(1000); // 1 초 동안 정지
	}
	// printf("송신 데이터 크기 : %d\n", sendsize);
	// 데이터 크기 확인 시 사용

	// socket dll 종료
	closesocket(mulsock);
	WSACleanup();

	return 0;
}