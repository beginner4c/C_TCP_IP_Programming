/*UDP 클라이언트에서 파일을 하나 만들고 데이터를 넣어
저장한 후 파일의 내용을 읽어 UDP 서버에게 전송,
서버는 받은 데이터를 파일에 저장한다*/
// define 된 값들은 F12 키를 통해서 확인이 가능하다

// 전처리기 구성
#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main() {
	// winsock dll 로드
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// socket 생성
	SOCKET s;
	s = socket(AF_INET, SOCK_DGRAM, 0); // IPv4, UDP, 프로토콜 옵션
	// AF_INET과 SOCK_DGRAM은 2를 define한 값이다
	if (s == INVALID_SOCKET) {
		printf("socket error");
		return -1;
	}

	// 데이터 송신
	SOCKADDR_IN SRVaddr; // IP 주소, 포트 번호, IPv 를 넣어줄 구조체 생성
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // 구조체 초기화

	SRVaddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // 구조체에 서버 측 ip 입력
	SRVaddr.sin_port = htons(12345); // 서버에 접근할 포트 번호 입력
	SRVaddr.sin_family = AF_INET; // ipv4 인지 ipv6 인지 넣어준다 

	FILE* fp;
	fp = fopen("c:\\Data.txt", "rb");
	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);

}