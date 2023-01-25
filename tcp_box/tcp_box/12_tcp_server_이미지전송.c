// �������� Ŭ���̾�Ʈ�� �̹��� ����

#pragma comment(lib,"ws2_32.lib")
#include<WinSock2.h>
#include<stdio.h>

main() {
	WSADATA wsa;

	// winsock dll load
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// ���� ����
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	// AF_INET = ipv4, SOCK_STREAM = TCP, protocol = null(0)
	if (s == INVALID_SOCKET) {
		printf("socket error\n");
		return -1;
	}

	// �ּ� ����
	// sturct sockaddr_in
	SOCKADDR_IN SRVaddr; // �ּ� ���� ������ ���� ����ü ����
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // ����ü 0 ���� �ʱ�ȭ

	SRVaddr.sin_family = AF_INET; // IPv4
	SRVaddr.sin_port = htons(12345); // host to network short 12345 (12345 �� ȣ��Ʈ���� ��Ʈ��ũ �������)
	SRVaddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // ip �ּ� �Է�
	// SRVddr.sin_addr.S_un.S_addr = ������ �ּ� 

	int errch = 0; // ���� üũ�� ���� ����
	errch = bind(s, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind �Լ��� ���� �ü���� ����� �޾��ش�
	if (errch == SOCKET_ERROR) {
		printf("bind error\n");
		return -1;
	}

	// ��Ʈ ����
	errch = listen(s, SOMAXCONN); // listen �Լ��� ���� ��Ʈ�� listen ���·� �����ش�
	if (errch == SOCKET_ERROR) {
		printf("listen error\n");
		return -1;
	}

	// ���� ���
	SOCKET CLTs; // ���� ����ü CLTs ����ü ����
	SOCKADDR_IN CLTaddr; // ip �� port �� �Ѱ��� ����ü ���� (IPv4�� ������ ����ü)
	memset(&CLTaddr, 0, sizeof(CLTaddr)); // CLTaddr ����ü �ʱ�ȭ
	int size = sizeof(CLTaddr); // CLTaddr ����ü ũ�⸦ size�� ��Ҵ�

	CLTs = accept(s, (SOCKADDR*)&CLTaddr, &size); // accept �Լ��� ���� ���濡�Լ� ��û�� ������ �����ϰ� �ȴ�
	if (CLTs == INVALID_SOCKET) {
		printf("accept error\n");
		return -1;
	}

	// ��� ����
	char path[256]; // ��θ� ���� �迭 ����
	memset(path, 0, sizeof(path)); // �迭 �ʱ�ȭ
	recv(CLTs, path, sizeof(path), 0); // recv �Լ��� ���� client ���� ���� ��ġ ������ path �� ����

	// ���� ũ�� �۽�
	FILE* fp; // FILE ����ü fp ���� 
	fp = fopen(path, "rb"); // fp �� path �迭�� ���� �־��ش�, ���� rb(�б� ���)
	fseek(fp, 0, SEEK_END); // fp Ŀ�� ��ġ�� 0 ���� ������ ���� ������ �̵���Ų��
	// fseek �� ������ Ŀ�� ��ġ ���� ����
	int fsize = ftell(fp); // ftell �� ���� fp Ŀ�� ��ġ������ ũ�⸦ fsize �� �����Ѵ�
	// client ������ fsize �� ũ�⸦ ���� ������ ���� �غ� �� �� �ִ�

	send(CLTs, (char*)&fsize, sizeof(fsize), 0); // send �Լ��� ���� ������ ũ�⸦ �����Ѵ�
	// ������� ����Ǹ� client �������� �ش� ������ ����� ���� �Լ��� ��ٸ���

	// ���� ������ �۽�
	char* sendbuf = (char*)malloc(fsize); // fsize ��ŭ ���� Ȯ��
	memset(sendbuf, 0, fsize); // Ȯ���� ������ 0���� �ʱ�ȭ

	fseek(fp, 0, SEEK_SET); // fp ������ Ŀ�� ��ġ�� ���� ������ ��ġ�Ѵ�
	fread(sendbuf, 1, fsize, fp); // sendbuf ������ 1byte ��ŭ fsize ��ŭ fp ���� �����´�
	fclose(fp);

	send(CLTs, sendbuf, fsize, 0); // ����� ������ client �� send �Լ��� ���� �����Ѵ�

	// ���� ���� �� dll ��ε�
	closesocket(CLTs);
	closesocket(s);
	WSACleanup();

	return 0;
}