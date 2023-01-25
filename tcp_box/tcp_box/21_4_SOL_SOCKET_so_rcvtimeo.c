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

	int opt = 0;
	int optlen = sizeof(opt);

	getsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&opt, &optlen);
	if (opt == 0) {
		printf("�⺻ �� : %d\n", opt);
	}

	opt = 3000; // 3 ��

	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&opt, optlen); // recvfrom �� timeout�� 3 �� �ش�
	// 3�� ���� �����Ͱ� ������ ������ recvfrom �Լ��� �����Ѵ�
	// socket handle ��, level option, option �̸�, timeout ���� ��, ���� ���� ũ��

	printf("3�� ���� ������ ���� ���� �� : %d\n", opt); // ������ �� Ȯ��

	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&opt, optlen); // sendto �� timeout �� 3 �� �ش�
	// 3�� ���� �����Ͱ� �������� ������ sendto �Լ��� �����Ѵ�.
}