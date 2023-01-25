/*
udp 이미지 파일 다운로드
클라이언트가 경로를 전송하면 서버는 수신받은 경로를 통해서
이미지 파일을 읽어 클라이언트에게 송신
클라이언트는 수신받은 파일을 이미지 파일로 저장
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

	// 통신 대상의 주소 구조체
	SOCKADDR_IN recvaddr; // 주소 구조체 생성
	int recvlen = sizeof(recvaddr); // 주소 구조체 크기 저장

	char path[256]; // 경로를 수신할 배열 생성
	memset(path, 0, sizeof(path)); // 배열 초기화
	recvfrom(UDPs, path, sizeof(path), 0, (SOCKADDR*)&recvaddr, &recvlen); // client로 부터 경로 정보 수신
	// socket handle 값, 수신할 배열, 배열의 크기, option, 수신할 주소 구조체, 주소 구조체 크기
	printf("경로 : %s\n", path); // 경로확인

	// 데이터 전송
	FILE* fp; // FILE 생성
	fp = fopen(path, "rb"); // 수신한 경로, 읽기 모드
	fseek(fp, 0, SEEK_END); // fp 의 커서 위치를 제일 끝에서 0 만큼 이동
	int datasize = ftell(fp); // fp 의 커서 위치까지 크기를 저장
	fclose(fp); // 파일 종료

	sendto(UDPs, (char*)datasize, sizeof(datasize), 0, (SOCKADDR*)&recvaddr, recvlen); // client 로 데이터 송신
	// socket handle 값, 보낼 데이터, 데이터 크기, option, client 주소 구조체, 주소 구조체 크기

	char* sendbuf = (char*)malloc(datasize); // 보낼 데이터 크기만큼 동적할당 공간 생성
	memset(sendbuf, 0, datasize); // 동적할당 공간 초기화

	fp = fopen(path, "rb"); // 수신한 경로, 읽기 모드
	fread(sendbuf, datasize, 1, fp); // sendbuf 에 datasize 만큼 한 번 반복해서 fp의 데이터를 저장
	fclose(fp); // 파일 종료

	char udpbuf[1024]; // 보낼 데이터를 담을 배열 생성
	memset(udpbuf, 0, sizeof(udpbuf)); // 배열 초기화
	int sendsize = sizeof(udpbuf); // 보낼 데이터 크기
	int totalsize = 0; // 보낸 데이터의 총 크기
	printf("%d\n", datasize); // 보낼 데이터 크기 확인
	int size = 0; // 보낸 데이터 크기

	while (1) { // break 를 만날 때까지 반복
		memcpy(udpbuf, &sendbuf[totalsize], sendsize); // udpbuf 에 sendbuf 를 sendsize 만큼 데이터 복사
		// heap 지역에 저장된 데이터를 배열에 다시 저장한다
		size = sendto(UDPs, udpbuf, sendsize, 0, (SOCKADDR*)&recvaddr, recvlen); // 배열의 데이터를 client에 전송
		// socket handle 값, 보낼 데이터, 보낼 데이터 크기, option, client 주소 구조체, 주소 구조체 크기

		if (size == 0) // 보낸 데이터가 0 인 경우 break;
			break;

		datasize -= size; // 남은 보내야 하는 데이터 크기에서 보낸 데이터를 뺀다

		if (datasize < size) // 남은 보내야하는 데이터 크기가 보낸 데이터 보다 작을 경우
			sendsize = datasize; // 보낼 데이터 크기는 남은 데이터 크기로 바꾼다

		totalsize += size; // 보낸 데이터의 총 크기는 보낸 데이터만큼 더해준다

		printf("보낸 데이터 : %d\n", size); // 보낸 데이터 크기 확인
	}

	// socket dll 종료
	closesocket(UDPs);
	WSACleanup();

	return 0;
}