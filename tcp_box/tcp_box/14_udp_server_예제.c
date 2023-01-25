#include<winsock2.h>
#include<stdio.h>
#pragma commnet(lib, "ws2_32.lib")

// Server �� ���

main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET udpS;
	udpS = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM = UDP ���
	// TCP ��Ŀ����� SOCK_STREAM �� �־��־�����
	if (udpS == INVALID_SOCKET) {
		printf("socket error\n");
		return -1;
	}

	// ���� �ּ� ����ü
	SOCKADDR_IN SRVAddr;
	SRVAddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // SERVER IP
	SRVAddr.sin_port = htons(15437);
	SRVAddr.sin_family = AF_INET;

	// ���Ͽ� �ּ� ����
	int error;
	error = bind(udpS, (SOCKADDR*)&SRVAddr, sizeof(SRVAddr)); // bind �Լ��� ���� �ü������ ��� ����
	if (error == SOCKET_ERROR) { // bind �Լ� ���� �� 
		printf("bind error\n");
		return -1;
	}

	SOCKADDR_IN CTAddr; // client �� ���� �ּҸ� ���� �ּ� ����ü
	int CTAddrLen = sizeof(CTAddr); // ����ü ũ�⸦ ����
	char buf[512]; // �������κ��� ���ƿ� �����͸� ������ �迭

	error = recvfrom(udpS, buf, sizeof(buf), 0, (SOCKADDR*)&CTAddr, &CTAddrLen); // �������κ��� ���ƿ� �����͸� ���Թ��� �Լ�
	if (error == SOCKET_ERROR) { // recvfrom �Լ� ���� ��
		printf("recvfrom error\n");
		return -1;
	}
	printf("���� ������ : %s\n", buf); // buf �� �޾ƿ� �����͸� ���

	// ���ϰ� dll ����
	closesocket(udpS);
	WSACleanup();
	return 0;
}