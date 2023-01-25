// tcp Ŭ���̾�Ʈ���� ������ �ϳ� ����� �����͸� �־� ������ ��
// ������ ������ �о� tcp �������� ����, ������ ���� �����͸� ���Ͽ� ����

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main(int agrc, char *argv[]) {

	// winsock dll load
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// ���� ����
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

	// ������ ���� ��û
	int errch = 0;
	errch = connect(s,(SOCKADDR*)&SRVAddr, sizeof(SRVAddr));
	if (errch == SOCKET_ERROR) {
		printf("connect error\n");
		return -1;
	}

	// ������ �۽�
	char sendbuf[1024]; // ������ �۽ſ� �迭 ����
	memset(sendbuf, 0, sizeof(sendbuf)); // �ش� �迭 0 ���� �ʱ�ȭ

	FILE* fp = fopen("test.txt", "r"); // �� c ������ ��ġ�� ���� test.txt �� �б�� �����ϰڴ� 
	if (fp == NULL) { // fopen �� �������� ���
		printf("������ �����ϴ�");
		return -1;
	}
	// fread : ���� �������� �Ҷ� ����ϴ� �Լ�
	fread(sendbuf, 1, sizeof(sendbuf), fp); // sendbuf : ������ ����, 1 : ũ��, count ��, ���Ͽ� ���� ����
	// fp ��� ���Ͽ� ����� ���� 1 byte �� sendbuf ũ�⸸ŭ �ݺ��ؼ� sendbuf��� ������ ������ ���̴�
	// �����ϰ� fp �� ������ sendbuf �� �������� �ȴ�
	fclose(fp); // �����ߴ� ���� �ݾ��ش�

	int size;
	// server�� message �� ���� send �Լ�
	size = send(s, sendbuf, sizeof(sendbuf), 0); // socket handle ��, ���� ������, ���� ������ ũ��, �ɼ� �� 0
	printf("�۽� ������ ũ�� : %d\n", size); // ���� �����Ͱ� �������̶�� ��µ� ��

	// ���� ����
	closesocket(s);

	// winsock dll unload
	WSACleanup();

	return 0;
}