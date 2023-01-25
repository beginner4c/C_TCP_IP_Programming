// UDP 서버를 계산기서버로 구현
// UDP 클라이언트에서 데이터를 전송하고
// UDP 서버에서는 산술 처리 결과 값을
// DUP 클라이언트에게 전송하게 구성

struct test {
	int num1;
	int num2;
	char op;
};

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

int main() {
	WSADATA wsa;
	// winsock dll 로드
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// 소켓 생성
	SOCKET s;
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET) { // 소켓 생성 실패 시 예외 처리
		printf("socket error!\n");
		return -1;
	}

	// 주소 결합
	// struct sockaddr_in
	SOCKADDR_IN SRVaddr; // 주소 구조체 변수 생성
	memset(&SRVaddr, 0, sizeof(SRVaddr));

	SRVaddr.sin_family = AF_INET; // ipv4 사용
	SRVaddr.sin_port = htons(12345); // 포트 번호 입력
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.1.1"); // server 에 대한 ip 주소
	// SRVaddr.sin_addr.S_un.S_addr = 서버 아이피주소;

	int errch = 0;
	errch = bind(s, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind 함수를 통해 os에 허락받는다
	if (errch == SOCKET_ERROR) { // bind 실패 시 예외 처리
		printf("bind error!\n"); // 보통 서버 아이피를 잘못 넣을 경우 발생한다
		return -1;
	}

	// 데이터 수신
	char buf[1024]; // recvbuf라는 1MB 공간 생성
	memset(buf, 0, sizeof(buf)); // recvbuf 초기화

	SOCKADDR_IN CLTaddr; // 주소 구조체 변수 생상 (recvfrom 함수를 사용하기 위해)
	int CLTlen = sizeof(CLTaddr); // 주소 구조체 크기 CLTlen 에 저장
	memset(&CLTaddr, 0, CLTlen); // 주소 구조체를 0 으로 초기화

	struct test ca;
	int result = 0;
	recvfrom(s, (char*)&ca, sizeof(ca), 0, (SOCKADDR*)&CLTaddr, &CLTlen); // 클라이언트 데이터를 ca에 저장
	// CLTaddr 에는 클라이언트 정보를 넣어준다 (SOCKADDR_IN 을 SOCKADDR 로 캐스팅해야 오류가 없다)
	
	if (ca.op == '+')
		result = ca.num1 + ca.num2;
	if (ca.op == '-')
		result = ca.num1 - ca.num2;
	if (ca.op == '*')
		result = ca.num1 * ca.num2;
	if (ca.op == '/')
		result = ca.num1 / ca.num2;

	sendto(s, (char*)&result, sizeof(result), 0, (SOCKADDR*)&CLTaddr, sizeof(CLTaddr));
	// 소켓 종료 및 dll 언로드
	closesocket(s);
	WSACleanup();

	return 0;
}