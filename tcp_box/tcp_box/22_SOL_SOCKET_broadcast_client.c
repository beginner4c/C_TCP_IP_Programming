// ��ó���� ����
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>
#include<ws2tcpip.h> // �ɼ� ���

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

	// ��ε� ĳ��Ʈ Ȱ��
	BOOL opt = TRUE; // ������ ���� BOOL ����
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt)); // broadcast Ȱ��ȭ
	// socket handle ��, level option, option �̸�, Ȱ��ȭ ����, Ȱ�� ���ο� ���� ũ��

	// ������ �۽�
	SOCKADDR_IN SRVaddr; // ���� �ּ� ����ü
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // �ּ� ����ü �ʱ�ȭ

	SRVaddr.sin_addr.s_addr = inet_addr("192.168.41.255"); // broadcast �� ���� ip �ּ� (class�� ���� 255)
	SRVaddr.sin_port = htons(12345); // ����� ��Ʈ ��ȣ
	SRVaddr.sin_family = AF_INET; // ipv4

	char sendbuf[1024]; // ���� �޽����� ������ ����
	memset(sendbuf, 0, sizeof(sendbuf)); // ���� ���� �ʱ�ȭ

	printf("input data : ");
	scanf("%s", sendbuf); // ���� �޽��� �Է�

	int sendsize = 0; // ���� ������ ũ�� Ȯ�ο� ����
	sendsize = sendto(sock, sendbuf, strlen(sendbuf), 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // ������ ����
	// socket handle ��, ���� ������, ���� ������ ũ��, option, �ּ� ����ü, �ּ� ����ü ũ��

	printf("�۽� ������ ũ�� : %d\n", sendsize); // ������ ũ�� Ȯ��

	// socket, dll ����
	closesocket(sock);
	WSACleanup();

	return 0;
}