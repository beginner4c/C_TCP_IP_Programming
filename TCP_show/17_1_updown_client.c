#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

typedef struct u {
	int num;
	char str[1024];
}ST;

main() {
	// winsock dll �ε�
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// ipv4 �� tcp �� ������ ���� ���� ����
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("socket error\n");
		return -1;
	}

	SOCKADDR_IN addr; // SOCKADDR_IN >>> ipv4 �� ������ �ּҿ� ��Ʈ�� ���� ����ü ����
	addr.sin_family = AF_INET; // ipv4 ����
	addr.sin_port = htons(12345); // ��Ʈ ��ȣ 12345 �� host ���Ŀ��� network ���·�
	addr.sin_addr.s_addr = inet_addr("172.22.200.48"); // ������ ��ȣ ����

	// connect �Լ��� ���� ������ ã�ư���
	int error = connect(s, (struct sockaddr*)&addr, sizeof(addr));
	if (error == SOCKET_ERROR) { // connect ���� ��
		printf("connect error\n");
		return -1;
	}

	// �����͸� ���� ������ ����ü ����
	char buf[500];
	int user;
	ST st;
	// ���� �� ���� ��� ���Ӱ� �����͸� ������
	while (1) {
		memset(&st, 0, sizeof(st)); // ����� �� ����ü 0 ���� �ʱ�ȭ
		printf("���� ������ �Է� : ");
		scanf("%d", &user); // ���� ������ �Է�
		int len = send(s, (char*)&user, sizeof(user), 0); //send �Լ��� ���� ������ �Է��� �����͸� �ѱ��
		// int ���� �ڷ�� char ���·� casting �ؼ� ������ �Ѵ�
		recv(s, (char*)&st, sizeof(st), 0); // �������� ���� �����͸� st �� �����Ѵ�
		printf("%s\n", st.str); // st ����ü�� �������� ���޹��� str ���� ���
		if (st.num == 1) // ������ ��� while ���� ����������
			break;
	}
	closesocket(s);
	WSACleanup();
	return 0;
}