#include<winsock2.h>
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib")

// Client 의 경우

main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET CTc; // 소켓 구조체 선언
	CTc = socket(AF_INET, SOCK_DGRAM, 0); // 소켓 생성
	// tcp 방식의 경우 SOCK_DGRAM 이 아닌 SOCK_STREAM 을 넣어준다
	if (CTc == INVALID_SOCKET) { // 소켓 생성 실패 시
		printf("SOCKET ERROR\n");
		return -1;
	}

	SOCKADDR_IN srvaddr; // 서버에 대한 주소를 담을 구조체 선언
	srvaddr.sin_family = AF_INET; // IPv4
	srvaddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // SERVER IP 입력
	srvaddr.sin_port = htons(15437); // SERVER PORT 입력

	char buf[512] = "HELLO"; // 서버에 전송할 데이터 배열
	int error;

	error = sendto(CTc, buf, sizeof(buf), 0, (SOCKADDR*)&srvaddr, sizeof(srvaddr));
	// 해당 함수를 통해 서버에 buf 에 있는 데이터 전송
	// send 에 비해 추가된 것은 서버 주소 구조체와 그에 대한 크기
	if (error == SOCKET_ERROR) { // sendto 함수 실패 시
		printf("sendto error\n");
		return -1;
	}

	printf("전송 완료\n"); // sendto 함수를 통해 문제 없이 다 전송했을 경우
	// tcp 와 다르게 그냥 연결없이도 뿌리게 되므로 서버에서 받지 않더라도 문제가 없을 경우 출력된다 

	// 사용한 socket 과 dll 정리
	closesocket(CTc);
	WSACleanup();

	return 0;
}