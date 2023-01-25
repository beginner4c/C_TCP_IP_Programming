// UDP 서버를 계산기서버로 구현
// UDP 클라이언트에서 데이터를 전송하고
// UDP 서버에서는 산술 처리 결과 값을
// DUP 클라이언트에게 전송하게 구성

// 계산을 위해 서버 측에 보낼 구조체
struct test { 
	int num1; // 계산할 숫자
	char op; // 연산자
	int num2; // 계산할 숫자
};

// 전처리기 구성
#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main() {
	// winsock dll 로드
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	// define된 값들은 F12 번을 통해서 확인이 가능하다
	// define된 값들을 확인 후에는 ctrl + F4 를 통해서 해당 화면을 종료할 수 있다

	// socket 생성
	SOCKET s; // 정수 형태의 자료형 SOCKET
	// s 는 핸들값(== 무엇인가를 조종할 수 있는 값)
	s = socket(AF_INET, SOCK_DGRAM, 0); // IPv4, UDP, 프로토콜 옵션
	// AF_INET과 SOCK_DGRAM은 2를 define한 값이다
	if (s == INVALID_SOCKET) { // 예외처리를 통해 s 에 제대로 된 값이 들어가지 않은 경우를 확인한다
		printf("socket error");
		return -1;
	}

	// 데이터 송신
	SOCKADDR_IN SRVaddr; // IP 주소, 포트 번호, IPv 를 넣어줄 구조체 생성
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // SRVaddr 구조체를 0으로 초기화

	// 서버에 대한 정보를 SRVaddr 에 넣어준다
	SRVaddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // 구조체에 서버 측 ip 입력
	// SRVaddr.sin_addr.S_un.S_addr == SRVaddr.sin_addr.s_addr (둘은 동일하다)
	// s_addr 은 S_un.S_addr 을 define 한 값이다
	SRVaddr.sin_port = htons(12345); // 서버에 접근할 포트 번호 입력
	// 일반적으로 사용하는 intel cpu 의 경우 littel endian 방식이지만
	// network programming 에서는 big endian 방식을 사용하기 때문에 htons가 필요하다
	SRVaddr.sin_family = AF_INET; // ipv4 인지 ipv6 인지 넣어준다 
	// ipv4 = AF_INET = 2, ipv6 = AF_INET6 = 23

	// 계산할 값 보내기
	printf("데이터 입력 : ");

	struct test ca; // 구조체 ca 생성
	scanf("%d %c %d", &ca.num1, &ca.op, &ca.num2); // 계산할 값과 연산자 입력

	sendto(s, (char*)&ca, sizeof(ca), 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // 서버 측에 구조체 ca 전달
	// SOCKADDR_IN인 SRVaddr 을 SOCKADDR 로 캐스팅해야 오류가 없다

	// 결과값 받기
	int result = 0;
	recvfrom(s, (char*)&result, sizeof(result), 0, 0, 0); // 서버측에서 보낸 값을 result 에 저장

	printf("%d %c %d = %d\n", ca.num1, ca.op, ca.num2, result);

	// 소켓 종료
	closesocket(s);
	// dll 언로드
	WSACleanup();

	return 0;
}