#include<winsock2.h>
#include<stdio.h>
#pragma commnet(lib, "ws2_32.lib")

// Server 의 경우

main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET udpS;
	udpS = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM = UDP 방식
	// TCP 방식에서는 SOCK_STREAM 을 넣어주었었다
	if (udpS == INVALID_SOCKET) {
		printf("socket error\n");
		return -1;
	}

	// 서버 주소 구조체
	SOCKADDR_IN SRVAddr;
	SRVAddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // SERVER IP
	SRVAddr.sin_port = htons(15437);
	SRVAddr.sin_family = AF_INET;

	// 소켓에 주소 연결
	int error;
	error = bind(udpS, (SOCKADDR*)&SRVAddr, sizeof(SRVAddr)); // bind 함수를 통해 운영체제에게 허락 받음
	if (error == SOCKET_ERROR) { // bind 함수 실패 시 
		printf("bind error\n");
		return -1;
	}

	SOCKADDR_IN CTAddr; // client 에 대한 주소를 받을 주소 구조체
	int CTAddrLen = sizeof(CTAddr); // 구조체 크기를 저장
	char buf[512]; // 상대방으로부터 날아온 데이터를 저장할 배열

	error = recvfrom(udpS, buf, sizeof(buf), 0, (SOCKADDR*)&CTAddr, &CTAddrLen); // 상대방으로부터 날아온 데이터를 대입받을 함수
	if (error == SOCKET_ERROR) { // recvfrom 함수 실패 시
		printf("recvfrom error\n");
		return -1;
	}
	printf("수신 데이터 : %s\n", buf); // buf 에 받아온 데이터를 출력

	// 소켓과 dll 정리
	closesocket(udpS);
	WSACleanup();
	return 0;
}