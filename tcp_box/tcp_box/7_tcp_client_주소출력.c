// tcp Ŭ���̾�Ʈ�� �������� �� ���� �Լ��� argument�� �̿��Ͽ�
// tcp ������ ip/port �ּҸ� �Է��Ͽ� �� ���α׷��� �����ϰ� �����ϱ�

#pragma comment(lib, "ws2_32.lib")
#include<WinSock2.h>
#include<stdio.h>

main(int argc, char* argv[]) {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // ���� �Լ� ��� �غ� (winsock.dll load)

	SOCKET s; // SOCKET ����
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("socket_error");
		return -1;
	}

	SOCKADDR_IN ser_addr; // ����(����)�� ���� ������ �Է��� ����ü
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]); // argv �迭�� ���� ���濡 �����ϰ� �ȴ�
	// argv 1 �� ������ ip address �� �����ϰڴ�
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(atoi(argv[2])); // argv 2 �� ������ ������ port number �� �����ϰڴ�
	// ���ڿ� ���·� �Է¹޾ұ� ������ 2byte ���������� �����ִ� ���� atoi (a to int) �Լ� �̴�

	int error = 0;
	error = connect(s, (struct sockaddr*) & ser_addr, sizeof(ser_addr));
	if (error == SOCKET_ERROR) {
		printf("connect_error");
		return -1;
	}

	int len = 0;
	char buf[100] = "Hello";
	len = send(s, buf, sizeof(buf), 0);

	closesocket(s);
	WSACleanup();

	return 0;
}