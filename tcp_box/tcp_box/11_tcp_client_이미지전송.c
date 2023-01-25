// �̹����� �����غ���
// Ŭ���̾�Ʈ���� ������ �̹��� ����
// tcp server-client image file ����
// C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\�׸� ����\

// tcp client ���� image file �� �о�
// tcp size �� data �� server ���� �۽�

// tcp server�� Ŭ���̾�Ʈ�� ���� data�� �����Ͽ� C:\ �� ����
// ����� client �� ���� �̹��� ������ TCP �������� �� �� ����

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

	// connect ������ �Ϲ� client ���ϰ� �ٸ��� �ʴ�

	// ���� �����͸� �ְ� ���� ���� �ٸ��� ������ ���� �� jpg �� �߰��� ��
	// ������ ũ�� �۽�
	FILE* fp;
	fp = fopen("C:\\�ܿ�.jpg", "rb"); // �ܿ�.jpg �� rb ���(�б�)�� �����ϰڴ�
	fseek(fp, 0, SEEK_END); // fp ��� ������ Ŀ���� ���� ������ �̵�
	int fsize = ftell(fp); // ftell �Լ��� ���� ó������ ������ ũ�⸦ ���� �� �ִ�
	fclose(fp);

	send(s, (char*)&fsize, sizeof(fsize), 0); // ftell �� ���� ������ ũ�⸦ �����ϰ� �ȴ�
	// socket handle ��, (down casting)������ ũ��, ũ��, �ɼ� �� 0

	// ������ �۽�
	fp = fopen("C:\\�ܿ�.jpg", "rb"); // �ܿ�.jpg �� �ٽ� �� �� �о�� �����ϰڴ�
	char* sendbuf = (char*)malloc(fsize); // �޾ƿ� ũ�⸦ ���� heap ������ ���� ������ Ȯ���ϰڴ�
	memset(sendbuf, 0, fsize); // memset �� ���� sendbuf �� �ʱ�ȭ �����ش�
	fread(sendbuf, 1, fsize, fp); // fp �� ������ sendbuf ��� ������ 1 byte �� �޾ƿ� ũ�⸸ŭ �ݺ��� �����ش�
	fclose(fp); // ������ ������ �ٽ� �ݴ´�
	// �Ϲ����� ���� �ְ� ���� ���� �Ȱ���

	int size;
	size = send(s, sendbuf, fsize, 0); // sendbuf �� ����� ������ server�� �����ڴ�
	printf("�۽� ������ ũ�� : %d\n", size); // ���������� �۽ŵǾ��ٸ� ũ�Ⱑ �ٽ� ���ƿ´�

	// ���� ����
	closesocket(s);

	// dll unload
	WSACleanup();

	return 0;
}