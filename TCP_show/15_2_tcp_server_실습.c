// �̹����� �����غ���
// tcp server-client image file ����
// C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\�׸� ����\

// tcp client ���� image file �� �о�
// tcp size �� data �� server ���� �۽�

// tcp server�� Ŭ���̾�Ʈ�� ���� data�� �����Ͽ� C:\ �� ����
// ����� client �� ���� �̹��� ������ TCP �������� �� �� ����

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

	// client �� ���������� accept �Լ������� �� �ٸ� ���� ���� �����ϴ�

	// ������ ũ�� ����	
	int fsize = 0;
	recv(CLTs, (char*)&fsize, sizeof(fsize), 0); // client ���� ���� ������ ũ�⸦ fsize �� �����Ѵ�

	// ������ ����
	char* recvbuf = (char*)malloc(fsize); // ���� ������ ũ�⸸ŭ �����Ҵ��� �� ��������� Ȯ���Ѵ�
	memset(recvbuf, 0, fsize); // �����Ҵ�� ��������� �ʱ�ȭ �����ְڴ�

	int recvsize = 0; 
	recvsize = recv(CLTs, recvbuf, fsize, 0); // client �� ���� �����͸� �̸� �����Ҵ��� ��������� �����ϰڴ�
	printf("���� ������ ũ�� : %d\n", recvsize); // ���Ź��� ������ ũ�⸦ Ȯ��

	FILE* fp; // FILE ������ ������ ���� ����
	fp = fopen("C\\�ܿ�.jpg", "wb"); // ������ ���� ���·� �����ϰڴ�
	fwrite(recvbuf, 1, fsize, fp); // recvbuf �� ����� �����͵��� fp ��ġ�� ���� ������ְڴ�
	fclose(fp);

	// ���� ���� �� dll unload
	closesocket(s);
	closesocket(CLTs);
	WSACleanup();

	return 0;
}