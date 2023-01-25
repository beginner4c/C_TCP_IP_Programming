// 10 ���ʹ� �ܼ��� text �� �ƴ� file or image �� �����Ѵ�

// tcp client ���� ���� data size�� �˷��ְ�,
// tcp server �� client �� ���� data size ��ŭ
// ���� ������ ����� �����ϱ�

// tcp server ���忡���� client �� ���� data size�� �𸣱⿡
// size�� ���� �޾� ���۹��� size ��ŭ data �� ������

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

	// ������ ũ�� ����
	int fsize = 0;
	recv(CLTs, (char*)&fsize, sizeof(fsize), 0); // recv �Լ��� ���� client ���� ���ƿ� ũ�Ⱑ fsize �� ����ȴ�

	// ������ ����
	char* recvbuf = (char*)malloc(fsize + 1); // �޾ƿ� ũ�⸦ ���� ��������� �����Ҵ��ؼ� Ȯ���ϰ� �ȴ�
	// fsize + 1 �� ������ ������ ������ NULL ���� �����ϱ� ���ؼ��̴�
	memset(recvbuf, 0, fsize + 1); // �����Ҵ�� ������ ���� 0 ���� �ʱ�ȭ �Ѵ�

	recv(CLTs, recvbuf, fsize, 0); // �������� ���� ���ƿ� message �� �����Ѵ�
	printf("���� ������ : %s\n", recvbuf); // �޾ƿ� data Ȯ��

	FILE* fp; // FILE ������ ������ ����
	fp = fopen("DownData.txt", "ab"); // ab ���(append binary)�� �ش� ������ �����ϰ� �ȴ� == fp �� ������ ������ ����ȴ�
	fwrite(recvbuf, 1, fsize, fp); // �޾ƿ� �����͸� 1 byte �� fsize ��ŭ �ݺ��ؼ� fp �� �����ش� (DownData.txt �� ����)
	fclose(fp); // ������ ������ �ݴ´�

	// ���� ���� �� dll unload
	closesocket(CLTs);
	closesocket(s);
	WSACleanup();

	return 0;
}