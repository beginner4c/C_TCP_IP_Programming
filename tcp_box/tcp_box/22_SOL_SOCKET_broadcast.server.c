// ��ó���� ����
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>
#include<ws2tcpip.h>

int main() {
	// dll �ε�
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// socket ����
	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) {
		printf("socket error!\n");
		return -1;
	}

	// �ּ� ����
	// struct sockaddr_in SRVaddr;
	SOCKADDR_IN SRVaddr; // �ּ� ����ü ����
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // �ּ� ����ü �ʱ�ȭ

	SRVaddr.sin_family = AF_INET; // ipv4
	SRVaddr.sin_port = htons(12345); // ����� ��Ʈ ��ȣ
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // ������ ������ �ּ�
	// SRVaddr.sin_addr.S_un.S_addr = ������ �ּ�

	int errch = 0;
	errch = bind(sock, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind �Լ��� ���� os�� ���
	if (errch == SOCKET_ERROR) { // bind error �߻� �� ���� ó��
		printf("BIND ERROR\n");
		return -1;
	}

	// ������ ����
	char recvbuf[1024]; // �����͸� ������ ����
	memset(recvbuf, 0, sizeof(recvbuf)); // ���� ���� �ʱ�ȭ

	SOCKADDR_IN CLTaddr; // client �ּҸ� ������ �ּ� ����ü ����
	int CLTlen = sizeof(CLTaddr); // �ּ� ����ü ũ�� ����
	memset(&CLTaddr, 0, CLTlen); // �ּ� ����ü �ʱ�ȭ

	int recvlen = 0; // ������ ������ ũ�⸦ ������ ����
	recvlen = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, (SOCKADDR*)&CLTaddr, &CLTlen); // ������ ����
	// socket handle ��, ������ ���� ����, ���� ���� ũ��, option, client �ּ� ����ü, �ּ� ����ü ũ��

	printf("���� ������ ũ�� : %d\n", recvlen); // Ȯ�ο� ��¹�
	printf("���� ������ : %s\n", recvbuf);

	// socket, dll ����
	closesocket(sock);
	WSACleanup();
	
	return 0;
}