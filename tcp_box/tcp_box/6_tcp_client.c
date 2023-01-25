#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

// �翬�� listening ���� server �� �����Ƿ� connect �ܰ迡�� error �߻��� �����ϴ�

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET CiTc;
	CiTc = socket(AF_INET, SOCK_STREAM, 0);

	if (CiTc == INVALID_SOCKET) {
		printf("SOCKET ERROR\n");
		return -1;
	}

	// ������ ������ �ּ� ����ü
	SOCKADDR_IN srvAddr;
	int errorCheck;
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_addr.s_addr = inet_addr("172.22.200.48");
	srvAddr.sin_port = htons(22222);
	srvAddr.sin_family = AF_INET;

	// ������ ���� ��û
	errorCheck = connect(CiTc, (struct sockaddr*)(&srvAddr), sizeof(srvAddr));

	if (errorCheck == SOCKET_ERROR) {
		printf("CONNECT ERROR\n");
		return -1;
	}

	// ������ ������ ����
	char buf[100] = "HELLO SOCKET";
	int sendSize;
	sendSize = send(CiTc, buf, sizeof(buf), 0);
	printf("%d byte ���� �Ϸ�!\n", sendSize);

	closesocket(CiTc);
	WSACleanup();
	return 0;
}