/*
udp �̹��� ���� ���ε�
Ŭ���̾�Ʈ���� �̹��������� �����͸� �о� �������� ����
������ ���۹��� �����͸� �̹��� ���Ϸ� ����
*/

// ��ó���� ���� 
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>

int main() {
	// winsock ����
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // define �� �� MAKEWORD �� ���� ���� ������ wsa �� �־��ش�

	// socket ����
	SOCKET UDPs;
	UDPs = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, udp, protocol
	if (UDPs == INVALID_SOCKET) { // socket ���� ���� �߻� �� ���� ó��
		printf("SOCKET ERROR!\N");
		return -1;
	}

	// ������ �ּ� ����ü
	SOCKADDR_IN SRVaddr; // �ּ� ����ü ����
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // ������ ip �ּ�
	SRVaddr.sin_port = htons(22222); // ������ ����� ��Ʈ ��ȣ
	SRVaddr.sin_family = AF_INET; // ������ ����� ipv

	// �ּ� ����
	int error = 0;
	error = bind(UDPs, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind �Լ��� ���� os�� ����� ��´�
	if (error == SOCKET_ERROR) { // bind �Լ� ���� �� ���� ó��
		printf("BIND ERROR\n");
		return -1;
	}

	// ������ ����
	char buf[1024]; // client���� ������ �����͸� ������ ���
	memset(buf, 0, sizeof(buf)); // �迭 �ʱ�ȭ

	SOCKADDR_IN CLTaddr; // client �� ������ ���� �ּ� ����ü ����
	int CLTlen = sizeof(CLTaddr); // �ּ� ����ü�� ũ��
	memset((char*)&CLTaddr, 0, CLTlen); // �ּ� ����ü �ʱ�ȭ

	int fsize = 0; // client���� ���� �̹��� ������ ũ�⸦ Ȯ���� ��
	recvfrom(UDPs, (char*)&fsize, sizeof(fsize), 0, NULL, 0); // client�κ��� �����͸� ����
	// recvfrom �Լ��� ������ �� fsize���� �޾ƾ��ϴ� �̹��� ������ ũ�Ⱑ ����ȴ�

	char* recvbuf = (char*)malloc(fsize); // �̹��� ���� ũ�⸸ŭ �����Ҵ�
	memset(recvbuf, 0, fsize); // �����Ҵ� ���� �ʱ�ȭ

	int recvlen = 0; // ���� ������ ũ��
	int size = 0; // �����͸� ������ �迭�� ��ġ

	while (1) { // break �� ���� ������ �ݺ�
		recvlen = recvfrom(UDPs, buf, sizeof(buf), 0, (SOCKADDR*)&CLTaddr, &CLTlen); // client�κ��� ������ ����
		// ������ �� ������ buf�� ũ�Ⱑ recvlen�� ���� �ȴ�
		// socket handle ��, ������ �����͸� ������ ����, ������ ũ��, option, client �ּ� ����ü, �ּ� ����ü ũ��

		printf("������ ������ ũ�� : %d\n", recvlen); // ������ ������ ũ�� Ȯ��
		if (recvlen == 0) // ������ �����Ͱ� ���� ��� �ݺ��� Ż��
			break;

		memcpy(&recvbuf[size], buf, recvlen); // recvbuf�� buf�� ������ recvlen ��ŭ ����
		size += recvlen; // ������ �迭�� ��ġ�� recvlen ��ŭ �����ش�
	}

	// ������ �����͸� �̹��� ���Ϸ� ����
	FILE *fp; // ����ü FILE ����
	fp = fopen("C:\\Users\\asus\\Downloads\\udp_down_test.png", "wb"); // ������ ��ġ, ����
	fwrite(recvbuf, 1, fsize, fp); // recvbuf �� ������ 1byte �� fsize��ŭ �ݺ��� fp �� ����
	fclose(fp); // FILE �ݾ���

	// socket, dll ����
	closesocket(UDPs);
	WSACleanup();

	return 0;
}