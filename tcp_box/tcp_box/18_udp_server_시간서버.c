/*
time_t 자료형, struct tm 자료형, localtime() 함수, time() 함수에 대해서
알아보고 서버는 현재의 시간을 클라이언트에 전송 후 출력(시간서버를 만들자)
*/

// 전처리기 선언 
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>
#include<time.h>

int main() {
	// winsock 생성
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // define 된 값 MAKEWORD 를 통해 버전 정보를 wsa 에 넣어준다

	// socket 생성
	SOCKET UDPs;
	UDPs = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, udp, protocol
	if (UDPs == INVALID_SOCKET) { // socket 생성 오류 발생 시 예외 처리
		printf("SOCKET ERROR!\N");
		return -1;
	}

	// 서버의 주소 구조체
	SOCKADDR_IN SRVaddr; // 주소 구조체 생성
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // 서버의 ip 주소
	SRVaddr.sin_port = htons(22222); // 서버와 통신할 포트 번호
	SRVaddr.sin_family = AF_INET; // 서버와 통신할 ipv

	// 주소 결합
	int error = 0;
	error = bind(UDPs, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind 함수를 통해 os에 허락을 얻는다
	if (error == SOCKET_ERROR) { // bind 함수 실패 시 예외 처리
		printf("BIND ERROR\n");
		return -1;
	}

	// 데이터 수신
	SOCKADDR_IN CLTaddr; // client 의 정보를 받을 주소 구조체 생성
	int CLTlen = sizeof(CLTaddr); // 주소 구조체의 크기
	memset((char*)&CLTaddr, 0, CLTlen); // 주소 구조체 초기화

	char msg[256]; // 클라이언트의 메시지를 받아 저장할 곳
	memset(msg, 0, sizeof(msg)); // 저장할 장소 초기화

	recvfrom(UDPs, msg, sizeof(msg), 0, (SOCKADDR*)&CLTaddr, &CLTlen); // client로 부터 데이터 수신
	// socket handle 값, 저장할 장소, 저장할 장소의 크기, option, client 주소를 받을 주소 구조체, 주소 구조체 크기
	
	// 송신할 시간 계산
	time_t tm; // long 타입 구조체 자료형 time_t
	time(&tm); // time 이라는 함수가 만들어졌을 때 부터 현재의 시간을 초 단위로 tm 에 저장
	struct tm * lt = localtime(&tm); // localtime 함수를 통해 time.h 에 정의된 구조체 tm 에 데이터를 넣어준다;
	// tm 에는 초 단위로 저장이 되어있기 때문에 localtime 함수를 사용해서 구조체에 저장하는게 바람직하다

	char time_send[512]; // time_send 배열 생성
	memset(time_send, 0, sizeof(time_send)); // 배열 초기화

	sprintf(time_send, "오늘은 %d년 %d월 %d일 현재시각은 %d시 %d분 입니다.\n",
		lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min);

	sendto(UDPs, time_send, strlen(time_send), 0, (SOCKADDR*)&CLTaddr, CLTlen); // client에 데이터 전송
	// socket, 보낼 데이터, 데이터 크기, option, client 주소 구조체, 주소 구조체 크기

	printf("시간 %d년 %d월 %d일 %d시 %d분 을 전송했습니다.\n",
		lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min);

	// socket, winsock 종료
	closesocket(UDPs);
	WSACleanup();

	return 0;
}