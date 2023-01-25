/*
time_t 자료형, struct tm 자료형, localtime() 함수, time() 함수에 대해서
알아보고 서버는 현재의 시간을 클라이언트에 전송 후 출력(시간서버를 만들자)
*/

// 전처리기 선언 
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>

int main() {
	// winsock 생성
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // define 된 값 MAKEWORD 를 통해 버전 정보를 wsa 에 넣어준다

	// socket 생성
	SOCKET UDPc;
	UDPc = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, udp, protocol
	if (UDPc == INVALID_SOCKET) { // socket 생성 오류 발생 시 예외 처리
		printf("SOCKET ERROR!\N");
		return -1;
	}

	// 통신할 서버의 주소 구조체
	SOCKADDR_IN sendAddr; // 주소 구조체 생성
	sendAddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // 서버의 ip 주소
	sendAddr.sin_port = htons(22222); // 서버와 통신할 포트 번호
	sendAddr.sin_family = AF_INET; // 서버와 통신할 ipv

	char msg[256] = "시간 전송 요청합니다."; // 서버에게 보낼 메시지

	sendto(UDPc, msg, strlen(msg), 0, (SOCKADDR*)&sendAddr, sizeof(sendAddr)); // 서버로 데이터 전송
	// socket handle 값, 보낼 data, 보낼 data 길이, option, 서버의 주소 구조체, 주소 구조체 크기

	char time[512]; // 서버에게 받은 데이터를 저장할 곳
	memset(time, 0, sizeof(time)); // 저장장소 0으로 초기화

	SOCKADDR_IN recvAddr; // 서버의 주소를 받을 주소 구조체
	int recvLen = sizeof(recvAddr); // 주소 구조체의 크기
	memset((char*)&recvAddr, 0, recvLen); // 주소 구조체 초기화

	recvfrom(UDPc, time, sizeof(time), 0, (SOCKADDR*)&recvAddr, &recvLen); // 서버로부터 데이터 수신
	// socket handle 값, 받을 장소, 받는 장소의 크기, option, 서버 정보를 받을 주소 구조체, 주소 구조체 크기

	printf("%s\n", time); // 잘 받았는지 확인 차 출력

	// socket, winsock 종료
	closesocket(UDPc);
	WSACleanup();

	return 0;
}