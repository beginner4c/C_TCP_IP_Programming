#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // �ɼ� ���� �� �ʿ� ���
#pragma comment(lib, "ws2_32.lib")

// MULTICAST ��� => �� �� �ټ��� ��� ���

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp ���� ����
	SOCKET mulsock = socket(AF_INET, SOCK_DGRAM, 0);
	if (mulsock == INVALID_SOCKET) {
		printf("SOCKET ERROR!\n");
		return -1;
	}
	// ��Ƽĳ��Ʈ TTL �ɼ� ����
	int multtl = 64; // TTL �� 64
	setsockopt(mulsock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&multtl, sizeof(multtl));
	// setsockopt �� �ɼǰ� ����
	// socket handle ��, LEVEL ��, OPTION, ��Ƽĳ��Ʈ�� ���� TTL��, ��Ƽĳ��Ʈ�� ���� ũ��

	// �ּ� ����ü
	SOCKADDR_IN muladdr;
	memset(&muladdr, 0, sizeof(muladdr));
	muladdr.sin_addr.s_addr = inet_addr("233.3.3.3");
	muladdr.sin_family = AF_INET;
	muladdr.sin_port = htons(33333);

	// ������ ����
	char mulbuf[512] = "hello multicast";
	
	sendto(mulsock, mulbuf, sizeof(mulbuf), 0, (SOCKADDR*)&muladdr, sizeof(muladdr));
	// socket handle ��, char ������ ���� ����, ���� ���� ũ��, option, �ּ� ����ü, �ּ� ����ü ũ��

	// ���� ����
	closesocket(mulsock);
	WSACleanup();

	return 0;
}