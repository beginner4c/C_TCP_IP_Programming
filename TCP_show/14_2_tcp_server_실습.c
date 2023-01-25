// tcp����-Ŭ���̾�Ʈ ���� ���� ����
// echo server ��?
// Ŭ���̾�Ʈ�� "hello" ��� ���ڿ��� �۽��ϸ� ������
// "hello"�� ���� �� "hello" ���ڿ��� Ŭ���̾�Ʈ���� �۽���

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main() {
	WSADATA wsa;

	// winsock dll �ε�
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// ���� ����
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("socket error");
		return -1;
	}

	// �ּ� ����
	// struct sockaddr_in
	SOCKADDR_IN SRVaddr;
	memset(&SRVaddr, 0, sizeof(SRVaddr));

	// �ڱ� �ڽſ� ���� ������ ����ü�� �Է����ش�
	SRVaddr.sin_family = AF_INET;
	SRVaddr.sin_port = htons(12345);
	SRVaddr.sin_addr.s_addr = inet_addr("172.22.200.48");
	// SRVaddr.sin_addr.S_un.S_addr = ������ �ּ�

	int errch = 0;
	errch = bind(s, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind �Լ��� ���� �ü������ ����� �޴´�
	if (errch == SOCKET_ERROR) {
		printf("bind error");
		return -1;
	}
	
	// ��Ʈ ����
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

	CLTs == accept(s, (SOCKADDR*)&CLTaddr, &size); // accept �Լ��� ���� ���濡�Լ� ��û�� �� ������ ����Ѵ�
	// ���� ���濡�Լ� connect �Լ��� ���� ��û�� ���� accept �Լ��� ���� �ް� �ȴ�
	if (CLTs == INVALID_SOCKET) {
		printf("accpet error");
		return -1;
	}

	printf("[%s] : %d", inet_ntoa(CLTaddr.sin_addr), ntohs(CLTaddr.sin_port));

	// ������ ���� 
	// client �� send �Լ��� ���� ���� �����͸� �����ؾ� �Ѵ�
	char recvbuf[1024]; // ���޹��� �����͸� ������ ��
	memset(recvbuf, 0, sizeof(recvbuf)); // ����� �ʱ�ȭ

	int recvsize = 0; // 
	recvsize = recv(CLTs, recvbuf, sizeof(recvbuf), 0); // recvbuf �� ������ ���� �޼����� �����ϰ� �ش� ũ�⸦ �����Ѵ�
	printf("%s\n", recvbuf);
	printf("���� ������ ũ�� : %d\n", recvsize);

	send(CLTs, recvbuf, strlen(recvbuf), 0); // �޾ƿ� �޼����� �״�� �ٽ� ������ �ȴ�

	// ���� ���� �� dll unload
	closesocket(s);
	WSACleanup();
	return;
}