#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

// server client 둘 다 구현했지만 send 한 적 없기에 당연히 error 발생이 맞다

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // MAKEWORD 로 2.2 버전 넣어주고 wsa 를 구동한다

	SOCKET SRVs; // SOCKET 구조체 SRVs 선언
	SRVs = socket(AF_INET, SOCK_STREAM, 0); // 소켓 생성
	// AF_INET = ipv4, SOCK_STREAM = TCP, protocol = null(0)

	if (SRVs == INVALID_SOCKET) { // socket이 제대로 생성되지 않았을 경우
		printf("SOCKET ERROR\n");
		return -1;
	}

	SOCKADDR_IN SRVAddr; // 주소를 저장할 구조체 서버 선언
	memset(&SRVAddr, 0, sizeof(SRVAddr)); // memset = 초기화 작업 함수
	// 주소, 초기화 원하는 값, 그것에 대한 크기
	
	int errorCheck;

	// 구조체 내부에 있는 멤버들에 값을 넣는다
	SRVAddr.sin_family = AF_INET; // IPV4 = AF_INET
	SRVAddr.sin_port = htons(22222); // 포트 번호를 넣어준다
	SRVAddr.sin_addr.S_un.S_addr = inet_addr("172.22.200.48"); // inet_addr 함수로 문자열을 정수로 받아낸다
	// 주소 할당

	errorCheck = bind(SRVs, (struct sockaddr*)&SRVAddr, sizeof(SRVAddr));
	
	if (errorCheck == SOCKET_ERROR) {
		printf("BIND ERROR\n");
		return -1;
	}
	// 소켓 오픈
	errorCheck = listen(SRVs, SOMAXCONN);
	
	if (errorCheck == SOCKET_ERROR) {
		printf("LISTEN ERROR\n");
		return -1;
	}

	//클라이언트 소켓
	SOCKET CiTs; // CiTs 라는 소켓 선언
	// 클라이언트 주소 저장할 구조체
	SOCKADDR_IN CiTAddr; // 주소 구조체 선언
	memset(&CiTAddr, 0, sizeof(CiTAddr)); // 주소 구조체를 0 으로 초기화
	int CiTLen = sizeof(CiTAddr); // 주소 구조체의 크기
	//클라이언트 연결 허용
	CiTs = accept(SRVs, (struct sockaddr*)(&CiTAddr), &CiTLen);
	
	if (CiTs == INVALID_SOCKET) {
		printf("ACCEPT ERROR\n");
		return -1;
	}

	//클라이언트 데이터 수신
	char buf[100];
	int recvSize;
	memset(buf, 0, 100); // buf 를 0 으로 초기화 해주겠다
	recvSize = recv(CiTs, buf, sizeof(buf), 0);
	printf("수신 데이터 : %s\n", buf);
	printf("수신 데이터 크기 : %d\n", recvSize);

	closesocket(SRVs);

	WSACleanup();
	
	return 0;
}