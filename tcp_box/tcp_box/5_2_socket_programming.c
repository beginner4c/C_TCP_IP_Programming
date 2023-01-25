#pragma comment(lib, "ws2_32")
#include<winsock2.h>

int main() {
	WSADATA wsa; // WSADATA �� ���� wsa ����
	WSAStartup(MAKEWORD(2, 2), &wsa); // �Լ��� 2.2 ������ wsa �ּҸ� �Ѱ��ش�
	// �� �Ʒ����� socket �Լ� ��� ����

	SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0); // SOCKET �ڷ����� ���� ����
	// ipv4 �� tcp, null ���� �־� socket �Լ� �۵�

	if (tcp_sock == INVALID_SOCKET) { // socket �Լ��� ����� �� ������� ���
		printf("���� ���� �߻�");
		return 0;
	}

	printf("���� ����"); // socket �Լ��� ����� �۵����� ���
	closesocket(tcp_sock); // tcp_sock socket �� �ݾ��ش�

	WSACleanup(); // dll load ���� unload �� ����
	return 0;
}