/*
udp 이미지 파일 업로드
클라이언트에서 이미지파일의 데이터를 읽어 서버에게 전송
서버는 전송받은 데이터를 이미지 파일로 저장
*/

// 전처리기 구성
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>

int main() {
	// dll 로드
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // define 된 값 MAKEWORD 를 통해 버전 정보를 wsa 에 넣어준다

	// socket 생성
	SOCKET for_send; // socket for_send 생성
	for_send = socket(AF_INET, SOCK_DGRAM, 0); // socket에 ipv4, ip protocol, option 넣어줌
	if (for_send == INVALID_SOCKET) { // socket 생성 에러 시 예외 처리
		printf("socket error\n");
		return -1;
	}

	// 데이터 송신
	SOCKADDR_IN SRVaddr; // 서버에 대한 주소 구조체 생성
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // 주소 구조체 초기화

	SRVaddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // 서버의 ip 주소
	SRVaddr.sin_port = htons(22222); // 서버와 통신할 포트 번호
	SRVaddr.sin_family = AF_INET; // 서버와 통신할 ipv

	// udp로 이미지 파일을 보낼 때
	// 1. 서버에 파일의 크기를 전송해 서버가 크기만큼 공간을 확보한다
	// 2. 그 후 이미지 파일을 전송한다

	FILE* fp; // 파일 fp 생성
	fp = fopen("C:\\Users\\asus\\Downloads\\군림보.png", "rb"); // fopen 함수로 이미지 파일을 읽어와 fp에 넣어줌
	fseek(fp, 0, SEEK_END); // fp의 커서를 파일의 끝으로 이동한 후 0 만큼 이동
	int fsize = ftell(fp); // fsize 는 fp의 크기 (ftell은 파일의 첫 부분에서 커서의 위치까지만 계산)

	sendto(for_send, (char*)&fsize, sizeof(fsize), 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // 서버에 이미지 크기 전송
	// socket handle 값, 파일의 크기 전송, 크기 전송, option, 서버의 주소 구조체, 주소 구조체 크기

	char* sendbuf = (char*)malloc(fsize); // fsize 크기만큼 동적 할당
	memset(sendbuf, 0, fsize); // 동적 할당된 공간 초기화

	fseek(fp, 0, SEEK_SET); // fp의 커서를 파일 제일 앞으로 가져와 0 만큼 이동
	fread(sendbuf, 1, fsize, fp); // sendbuf 에 1byte 씩 fsize 만큼 반복해서 fp 를 저장
	fclose(fp); // FILE 구조체 닫아줌
	
	char buf[1024]; // 1KB 배열 생성
	memset(buf, 0, sizeof(buf)); // 해당 배열 0으로 초기화

	// udp 통신에서는 보낼 수 있는 data 의 양이 한정되어 있기 때문에
	// 보낼 수 있는 양 안에서 반복해서 서버에 전송하도록 한다

	int size = 0; // 전송한 파일의 크기
	int sendsize = 1024; // 전송할 파일을 나눌 크기
	int totalsize = fsize; // 파일의 전체 크기

	while (1) { // break 까지 반복
		memcpy(buf, &sendbuf[size], sendsize); // sendbuf의 내용을 buf 에 sendsize 만큼 복사한다
		// buf 에 sendsize 인 1KB 만큼 sendbuf 배열의 내용을 복사

		sendsize = sendto(for_send, buf, sendsize, 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // 서버에 이미지 전송
		// socket handle 값, 보낼 데이터, 보낼 데이터 크기, option, 서버의 주소 구조체, 주소 구조체 크기
		// sendto 함수가 성공할 경우 sendsize에는 함수 속 보낼 데이터 크기가 들어갈 것이고
		// 실패할 경우 SOCKET_ERROR 가 반환된다

		printf("송신 데이터 크기 : %d\n", sendsize); // 보낸 데이터 크기 확인

		if (sendsize == 0) // 보낼 데이터가 0 이면 반복문 탈출
			break;

		totalsize -= sendsize; // 전송한 파일의 크기만큼 파일의 전체 크기를 뺀다

		size += sendsize; // 전송한 파일의 크기만큼 더해줘 sendbuf 배열 을 조정

		if (totalsize < sendsize) // 남은 전체 크기가 보낼 크기보다 작을 경우
			sendsize = totalsize; // 보낼 크기는 전체 크기가 된다
	}
	
	// socket, dll 종료
	closesocket(for_send);
	WSACleanup();

	return 0;
}