#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // �ɼ� ���� �� �ʿ� ���
#pragma comment(lib, "ws2_32.lib")

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp ���� ����
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) {
		printf("SOCKET ERROR!\n");
		return -1;
	}

	BOOL en = TRUE; // BOOL �ڷ����� ���� �־��ش�
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&en, sizeof(en)); // �ɼ� ����
	// socket handle ��, level ��, option �̸�, �ɼ� ��� ����, ��� ������ ũ��
	// socket �ɼǿ��� broadcast ȯ���� ����Ѵٰ� ������ ��

	SOCKADDR_IN serveraddr; // �ּ� ����ü ����
	serveraddr.sin_addr.s_addr = inet_addr("192.168.41.255"); // ip �ּ� �������� 255 �� �־��־�� �Ѵ�
	// �׷��� broadcast �� ���� �뿪�� ��� ������ �����͸� �ѷ��� �� �ֱ� �����̴�
	serveraddr.sin_family = AF_INET; // ip version
	serveraddr.sin_port = htons(22222); // ��Ʈ ��ȣ
}