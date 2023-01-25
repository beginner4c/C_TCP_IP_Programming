// UDP 에코 서버 - 클라이언트 구현

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
	
	char buf[512] = { 0 };
	printf("데이터 입력 : ");
	gets_s(buf, sizeof(buf));
	int sendsize = 0;
	sendsize = sendto(s, buf, sizeof(buf), 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr));
	// sendto 함수의 return 값은 int 이고 필요한 값들은
	// SOCKET, 보낼 데이터를 가진 주소, 보낼 크기, 옵션 값, 서버에 대한 주소 구조체 변수, 주소 구조체 변수 크기
	
	char new_buf[512] = { 0 };
	recvfrom(s, new_buf, sizeof(new_buf), 0, 0, 0); // 서버의 정보가 이미 있기 때문에 굳이 구조체를 넣지 않는다
	printf("송신 데이터 : %s\n", new_buf); // 아무런 오류없이 성공했을 경우 출력되는 메시지

	// 소켓 종료
	closesocket(s);
	// dll 언로드
	WSACleanup();

	return 0;
}