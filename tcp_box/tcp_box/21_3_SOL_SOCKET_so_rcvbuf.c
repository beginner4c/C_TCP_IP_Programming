#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // �ɼ� ���� �� �ʿ� ���
#pragma comment(lib, "ws2_32.lib")

// SO_RCVBUF ��� ���� 2
// ���� ������ ũ�⸦ �ٲ㺸�� ����

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp ���� ����
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, udp, option 0
	if (sock == INVALID_SOCKET) {
		printf("SOCKET ERROR!\n");
		return -1;
	}

	int rcvbufsize = 0; // ���� ������ ���� ���� ����
	int rcvbufsizelen = sizeof(rcvbufsize); // ������ ũ��

	getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvbufsize, &rcvbufsizelen); // ���� ������ ���� ���� Ȯ���Ѵ�
	// socket handle ��, level option, option �̸�, ����� ���� ����, ���� ���� ũ�⿡ ���� �ּ�

	printf("���� ���� %d\n", rcvbufsize); // ������ ���� ũ�� Ȯ��

	rcvbufsize *= 2; // ������ ���� ũ�� �ι� ����

	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&rcvbufsize, rcvbufsizelen);
	// socket handle ��, level option, option �̸�, ����� ���� ����, ���� ���� ũ�⿡ ���� �ּ�

	printf("���� ���� ������Ʈ : %d\n", rcvbufsize); // �ι�� ������ �� ��� Ȯ��
}