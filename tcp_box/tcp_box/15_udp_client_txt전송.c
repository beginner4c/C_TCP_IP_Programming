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

	FILE* fp;
	fp = fopen("C:\\Users\\asus\\Downloads", "rb"); // 읽어올 파일의 위치, 
	// r = rt (1 byte 씩 읽어온다), w = wt (1 byte 씩 써내린다)
	// 대용량을 옮길 때는 rb 혹은 wb 를 사용한다 (read binary or write binary)
	if (fp == NULL) {
		printf("파일을 찾을 수 없습니다");
		return -1;
	}
	fseek(fp, 0, SEEK_END); // fp 의 커서를 끝 부분으로 이동시켜서 0 만큼 이동
	// fseek(fp, -5, SEEK_END) 의 경우 커서를 끝에서 왼쪽으로 5 칸 이동시켜 위치시킨다
	int fsize = ftell(fp); // ftell을 통해 fp 의 커서 위치까지의 크기를 얻어와서 fsize에 저장한다

	char* sendbuf = (char*)malloc(fsize); // fsize 크기만큼 heap 영역에 크기 할당
	memset(sendbuf, 0, fsize); // sendbuf 의 공간을 fsize 크기만큼 0 으로 채워넣는다

	fseek(fp, 0, SEEK_SET); // fp 의 커서를 다시 첫 부분으로 이동시켜 0 만큼 이동
	fread(sendbuf, 1, fsize, fp); // sendbuf 에 1byte 씩 fsize 크기만큼 fp 를 읽어 옮겨주겠다
	fclose(fp);
	// printf("sendbuf : %s\n", sendbuf); 를 출력했을 때 값 끝에 이상한 값이 나오는 이유는
	// %s 는 NULL 값까지 읽는데 파일의 끝에는 NULL 값이 아닌 EOF 가 있기 때문이다
	// 해결 방법으론 malloc 시 fsize + 1 할당 후 sendbuf[fsize] 에 NULL을 넣는다

	int sendsize = 0;
	sendsize = sendto(s, sendbuf, fsize, 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr));
	// sendto 함수의 return 값은 int 이고 필요한 값들은
	// SOCKET, 보낼 데이터를 가진 주소, 보낼 크기, 옵션 값, 서버에 대한 주소 구조체 변수, 주소 구조체 변수 크기
	printf("송신 데이터 크기 : %d\n", sendsize); // 아무런 오류없이 성공했을 경우 출력되는 메시지

	// 소켓 종료
	closesocket(s);

	// dll 언로드
	WSACleanup();

	return 0;
}