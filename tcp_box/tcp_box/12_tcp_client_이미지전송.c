// ��ó���� ����
#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main() {
	// dll �ε�
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// ���� ����
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0); // socket �� ���� handle �� s
	// AF_INET = ipv4, SOCK_STREAM = TCP, protocol = null(0)
	if (s == INVALID_SOCKET) { // ���� ������ �������� ���
		printf("socket error\n");
		return -1;
	}

	SOCKADDR_IN SRVAddr; // SOCKET ����ü ����
	memset(&SRVAddr, 0, sizeof(SRVAddr)); // SRVAddr �� 0 ���� SRVAddr �� ũ�⸸ŭ �ʱ�ȭ�Ѵ�

	// server ip, port ���� �Է�
	SRVAddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // ������
	SRVAddr.sin_port = htons(12345); // ��Ʈ
	SRVAddr.sin_family = AF_INET; // IPv4

	int errch = 0;
	errch = connect(s, (SOCKADDR*)&SRVAddr, sizeof(SRVAddr));
	// socket handle ��, server �� �ּ� ����ü ����, �ּ� ����ü ũ��

	if (errch == SOCKET_ERROR) {
		printf("socke error\n");
		return -1;
	}

	// �ٿ� ���� ��� ����
	char path[256]; // ��ġ ���� ������ �迭
	memset(path, 0, sizeof(path)); // path �迭 �ʱ�ȭ
	printf("input path : ");
	scanf("%s", path); // ��� ���� �Է� �ޱ�

	send(s, path, strlen(path), 0); // send �Լ��� ���ؼ� ���� ������ ��θ� ���� ��

	// ������ ũ�� ����
	int fsize = 0;
	recv(s, (char*)&fsize, sizeof(fsize), 0); // recv �Լ��� ���¿����� char ���¸� �־��־�� �ϱ⿡ casting �Ѵ�
	// recv �Լ��� ���ؼ� fsize ���� ������ ���� ������ ũ�⸦ �����Ѵ�
	char* recvbuf = (char*)malloc(fsize); // heap ������ ������ ���� ������ ũ�⸸ŭ ������ Ȯ���Ѵ�
	memset(recvbuf, 0, fsize); // Ȯ���� ������ 0 ���� �ʱ�ȭ �Ѵ�

	// ������ ����
	recv(s, recvbuf, fsize, 0); // handle ��, �޾ƿ� ����, �޾ƿ� ũ��, �ɼ� ��(���� x)

	// ���� �����
	FILE* fp; // ���� ������� ���� fp ����
	fp = fopen("c:\\downdData.jpg", "wb"); // ���Ͽ� ���� ��ġ + Ȯ���ڸ� wb ���� ����
	fwrite(recvbuf, 1, fsize, fp); // recvbuf �� ����� ���� 1 byte �� fp �� fsize ��ŭ ����ϰڴ�
	fclose(fp); // file �� �ݾ��ش� 

	// ���� ����
	closesocket(s);

	// dll ��ε�
	WSACleanup();

	return 0;
}