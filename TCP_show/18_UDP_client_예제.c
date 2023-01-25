#include<winsock2.h>
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib")

// Client �� ���

main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET CTc; // ���� ����ü ����
	CTc = socket(AF_INET, SOCK_DGRAM, 0); // ���� ����
	// tcp ����� ��� SOCK_DGRAM �� �ƴ� SOCK_STREAM �� �־��ش�
	if (CTc == INVALID_SOCKET) { // ���� ���� ���� ��
		printf("SOCKET ERROR\n");
		return -1;
	}

	SOCKADDR_IN srvaddr; // ������ ���� �ּҸ� ���� ����ü ����
	srvaddr.sin_family = AF_INET; // IPv4
	srvaddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // SERVER IP �Է�
	srvaddr.sin_port = htons(15437); // SERVER PORT �Է�

	char buf[512] = "HELLO"; // ������ ������ ������ �迭
	int error;

	error = sendto(CTc, buf, sizeof(buf), 0, (SOCKADDR*)&srvaddr, sizeof(srvaddr));
	// �ش� �Լ��� ���� ������ buf �� �ִ� ������ ����
	// send �� ���� �߰��� ���� ���� �ּ� ����ü�� �׿� ���� ũ��
	if (error == SOCKET_ERROR) { // sendto �Լ� ���� ��
		printf("sendto error\n");
		return -1;
	}

	printf("���� �Ϸ�\n"); // sendto �Լ��� ���� ���� ���� �� �������� ���
	// tcp �� �ٸ��� �׳� ������̵� �Ѹ��� �ǹǷ� �������� ���� �ʴ��� ������ ���� ��� ��µȴ� 

	// ����� socket �� dll ����
	closesocket(CTc);
	WSACleanup();

	return 0;
}