#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // �ɼ� ���� �� �ʿ� ���
#pragma comment(lib, "ws2_32.lib")

// MULTICAST ��� => �� �� �ټ��� ��� ���

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp ���� ����
	SOCKET mulsock = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, socket dataGRAM, option
	if (mulsock == INVALID_SOCKET) { // ���� �� ���� ó��
		printf("SOCKET ERROR!\n");
		return -1;
	}

	// ������ �۽�
	SOCKADDR_IN srvaddr; // �ּ� ����ü ����
	memset(&srvaddr, 0, sizeof(srvaddr));

	srvaddr.sin_addr.s_addr = inet_addr("224.2.2.2"); // ip address
	srvaddr.sin_port = htons(12345); // port ��ȣ
	srvaddr.sin_family = AF_INET; // ip version

	// ��Ƽĳ��Ʈ TTL ��
	int multtl = 32; // ������ ttl �� ����
	setsockopt(mulsock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&multtl, sizeof(multtl)); // ttl �� ����
	// socket handle ��, level ��, option ��, char ���� ttl ��, ttl �� ũ��

	char sendbuf[1024]; // ���� �����͸� ������ ����
	memset(sendbuf, 0, sizeof(sendbuf)); // ������ ���� 0 ���� �ʱ�ȭ

	printf("input data : "); // ���
	scanf("%s", sendbuf); // �Է�

	// ������ �۽�
	int sendsize = 0; // ���� ������ ũ�� ����� ����
	sendsize = sendto(mulsock, sendbuf, strlen(sendbuf), 0, (SOCKADDR*)&srvaddr, sizeof(srvaddr)); // ������ ����
	// socket handle ��, ���� ������, ���� ������ ũ��, option, �ּ� ����ü, �ּ� ����ü ũ�� 
	printf("�۽� ������ ũ�� : %d\n", sendsize); // Ȯ��

	// socket, dll ����
	closesocket(mulsock);
	WSACleanup();

	return 0;
}