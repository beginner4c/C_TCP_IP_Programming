/*
udp 이미지 파일 업로드
클라이언트에서 이미지파일의 데이터를 읽어 서버에게 전송
서버는 전송받은 데이터를 이미지 파일로 저장
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
	char buf[1024]; // client에서 수신한 데이터를 저장할 장소
	memset(buf, 0, sizeof(buf)); // 배열 초기화

	SOCKADDR_IN CLTaddr; // client 의 정보를 받을 주소 구조체 생성
	int CLTlen = sizeof(CLTaddr); // 주소 구조체의 크기
	memset((char*)&CLTaddr, 0, CLTlen); // 주소 구조체 초기화

	int fsize = 0; // client에서 보낼 이미지 파일의 크기를 확인할 곳
	recvfrom(UDPs, (char*)&fsize, sizeof(fsize), 0, NULL, 0); // client로부터 데이터를 수신
	// recvfrom 함수가 성공할 시 fsize에는 받아야하는 이미지 파일의 크기가 저장된다

	char* recvbuf = (char*)malloc(fsize); // 이미지 파일 크기만큼 동적할당
	memset(recvbuf, 0, fsize); // 동적할당 공간 초기화

	int recvlen = 0; // 받은 데이터 크기
	int size = 0; // 데이터를 저장할 배열의 위치

	while (1) { // break 를 만날 때까지 반복
		recvlen = recvfrom(UDPs, buf, sizeof(buf), 0, (SOCKADDR*)&CLTaddr, &CLTlen); // client로부터 데이터 수신
		// 성공할 시 수신한 buf의 크기가 recvlen에 들어가게 된다
		// socket handle 값, 수신한 데이터를 저장할 공간, 공간의 크기, option, client 주소 구조체, 주소 구조체 크기

		printf("수신한 데이터 크기 : %d\n", recvlen); // 수신한 데이터 크기 확인
		if (recvlen == 0) // 수신한 데이터가 없는 경우 반복문 탈출
			break;

		memcpy(&recvbuf[size], buf, recvlen); // recvbuf에 buf의 내용을 recvlen 만큼 복사
		size += recvlen; // 저장할 배열의 위치를 recvlen 만큼 더해준다
	}

	// 수신한 데이터를 이미지 파일로 저장
	FILE *fp; // 구조체 FILE 생성
	fp = fopen("C:\\Users\\asus\\Downloads\\udp_down_test.png", "wb"); // 저장할 위치, 쓰기
	fwrite(recvbuf, 1, fsize, fp); // recvbuf 의 내용을 1byte 씩 fsize만큼 반복해 fp 에 쓴다
	fclose(fp); // FILE 닫아줌

	// socket, dll 종료
	closesocket(UDPs);
	WSACleanup();

	return 0;
}