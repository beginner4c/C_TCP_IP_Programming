// tcp Ŭ���̾�Ʈ���� ������ �ϳ� ����� �����͸� �־� ������ ��
// ������ ������ �о� tcp �������� ����, ������ ���� �����͸� ���Ͽ� ����

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main(int argc, char argv[]) {
	// winsock dll load
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// socket ����
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("socket error\n");
		return -1;
	}

	SOCKADDR_IN SRVAddr;
	memset(&SRVAddr, 0, sizeof(SRVAddr));

	// server ip, port number �Է�
	SRVAddr.sin_addr.s_addr = inet_addr("172.22.200.48");
	SRVAddr.sin_port = htons(12345);
	SRVAddr.sin_family = AF_INET;

	// bind �Լ��� ���� �ü������ ��� �ޱ�
	int errch = 0;
	errch = bind(s, (SOCKADDR*)&SRVAddr, sizeof(SRVAddr)); // bind �Լ��� ���� �ü������ ����� �޴´�
	if (errch == SOCKET_ERROR) {
		printf("bind error");
		return -1;
	}

	// listen �Լ��� ���� �ش� ��Ʈ�� listen ���·� ����
	errch = listen(s, SOMAXCONN); // listen �Լ��� ���� ���� ��Ʈ�� listen ���·� ������ش�
	if (errch == SOCKET_ERROR) {
		printf("listen error");
		return -1;
	}

	// ���� ���
	SOCKET CLTs;
	SOCKADDR_IN CLTaddr;
	memset(&CLTaddr, 0, sizeof(CLTaddr));
	int size = sizeof(CLTaddr);

	// accept ���·� client �� connect �� ��ٸ���
	CLTs = accept(s, (SOCKADDR*)&CLTaddr, &size); // accept �Լ� ȣ��
	if (CLTs == INVALID_SOCKET) {
		printf("accept error\n");
		return -1;
	}

	// ������ ����
	char recvbuf[1024]; // ������ ������ ������ ����
	memset(recvbuf, 0, sizeof(recvbuf)); // �ش� ������ �ʱ�ȭ

	recv(CLTs, recvbuf, sizeof(recvbuf), 0); // ���Ͽ� ���� �ڵ鰪, ������ ������ ����, ������ ���� ũ��, �ɼǰ�
	// recv �� �����ϸ� recvbuf �� �����Ͱ� ����ȴ�

	FILE* fp = fopen("data.txt", "w"); // fp �� �ش� ��ġ�� data.txt �� ���� ���� �����Ѵ�
	fwrite(recvbuf, 1, sizeof(recvbuf), fp); // recvbuf �� �ִ� �����͸� 1 byte �� recvbuf ũ�⸸ŭ �ݺ��ؼ� fp �� �����ش�

	fclose(fp);

	// socket ���� �� winsock dll unload
	closesocket(s);
	WSACleanup();

	return 0;
}