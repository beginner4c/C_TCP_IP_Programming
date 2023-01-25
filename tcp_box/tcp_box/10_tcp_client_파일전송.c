// 10 ���ʹ� �ܼ��� text �� �ƴ� file or image �� �����Ѵ�

// tcp client ���� ���� data size�� �˷��ְ�,
// tcp server �� client �� ���� data size ��ŭ
// ���� ������ ����� �����ϱ�

// tcp server ���忡���� client �� ���� data size�� �𸣱⿡
// size�� ���� �޾� ���۹��� size ��ŭ data �� ������

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>
#include<stdlib.h>

main(int agrc, char* argv[]) {

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
	errch = connect(s, (SOCKADDR*)&SRVAddr, sizeof(SRVAddr));
	if (errch == SOCKET_ERROR) {
		printf("connect error\n");
		return -1;
	}

	// ������ ũ�� �۽�
	FILE* fp; // ���� ������ ������ ���� ����
	fp = fopen("C:\\Data.txt", "rb"); // rb ���� �ش� ��ġ�� ������ �о���ڴ�
	fseek(fp, 0, SEEK_END); // ������ ����� ���ȴٸ� fp ������ Ŀ���� ���� ������ �̵���Ų��
	int fsize = ftell(fp); // ���� ���Ͽ� ���� ftell �Լ��� ���� ũ�⸦ �����ڴ�
	// ftell �Լ� : ������ ���������� ������ Ŀ�� ��ġ������ ũ�� ��� �Լ� 
	fclose(fp);

	send(s, (char*)&fsize, sizeof(fsize), 0); // ������ �� ũ�⸦ server �� ���� �����ϰڴ�
	// socket handle ��, ���Ͽ� ���� ũ��(char ���¸� ����)
	// ������ �� �Լ��� ���������� �޴´ٸ� ���۹��� ũ�⸸ŭ ���� ������ Ȯ������ ��

	// ������ �۽�
	fp = fopen("C:\\Data.txt", "rb"); // �ٽ� rb ���� �ش� ��ġ�� ������ �о�´�
	char* sendbuf = (char*)malloc(fsize); // �����Ҵ��� ���� fsize ��ŭ ũ�⸦ Ȯ���� �Ѵ�
	memset(sendbuf, 0, fsize); // �����Ҵ���� ������ ���� 0 ���� �ʱ�ȭ ��Ű�ڴ�
	fread(sendbuf, 1, fsize, fp); // ���� ���Ͽ� ����� ���� 1byte �� �ݺ��ؼ� sendbuf ��� ��������� �����ϰڴ� 
	fclose(fp);

	int size;
	size = send(s, sendbuf, fsize, 0); // sendbuf �� data �� server ������ �����ڴ�
	printf("�۽� ������ ũ�� : %d\n", size); // ���������� ������ ��� size �� ���� �������� ũ�Ⱑ ��µȴ�

	// ���� ����
	closesocket(s);

	// dll unload
	WSACleanup();

	return 0;
}