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
	// dll �ε�
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // define �� �� MAKEWORD �� ���� ���� ������ wsa �� �־��ش�

	// socket ����
	SOCKET for_send; // socket for_send ����
	for_send = socket(AF_INET, SOCK_DGRAM, 0); // socket�� ipv4, ip protocol, option �־���
	if (for_send == INVALID_SOCKET) { // socket ���� ���� �� ���� ó��
		printf("socket error\n");
		return -1;
	}

	// ������ �۽�
	SOCKADDR_IN SRVaddr; // ������ ���� �ּ� ����ü ����
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // �ּ� ����ü �ʱ�ȭ

	SRVaddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // ������ ip �ּ�
	SRVaddr.sin_port = htons(22222); // ������ ����� ��Ʈ ��ȣ
	SRVaddr.sin_family = AF_INET; // ������ ����� ipv

	// udp�� �̹��� ������ ���� ��
	// 1. ������ ������ ũ�⸦ ������ ������ ũ�⸸ŭ ������ Ȯ���Ѵ�
	// 2. �� �� �̹��� ������ �����Ѵ�

	FILE* fp; // ���� fp ����
	fp = fopen("C:\\Users\\asus\\Downloads\\������.png", "rb"); // fopen �Լ��� �̹��� ������ �о�� fp�� �־���
	fseek(fp, 0, SEEK_END); // fp�� Ŀ���� ������ ������ �̵��� �� 0 ��ŭ �̵�
	int fsize = ftell(fp); // fsize �� fp�� ũ�� (ftell�� ������ ù �κп��� Ŀ���� ��ġ������ ���)

	sendto(for_send, (char*)&fsize, sizeof(fsize), 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // ������ �̹��� ũ�� ����
	// socket handle ��, ������ ũ�� ����, ũ�� ����, option, ������ �ּ� ����ü, �ּ� ����ü ũ��

	char* sendbuf = (char*)malloc(fsize); // fsize ũ�⸸ŭ ���� �Ҵ�
	memset(sendbuf, 0, fsize); // ���� �Ҵ�� ���� �ʱ�ȭ

	fseek(fp, 0, SEEK_SET); // fp�� Ŀ���� ���� ���� ������ ������ 0 ��ŭ �̵�
	fread(sendbuf, 1, fsize, fp); // sendbuf �� 1byte �� fsize ��ŭ �ݺ��ؼ� fp �� ����
	fclose(fp); // FILE ����ü �ݾ���
	
	char buf[1024]; // 1KB �迭 ����
	memset(buf, 0, sizeof(buf)); // �ش� �迭 0���� �ʱ�ȭ

	// udp ��ſ����� ���� �� �ִ� data �� ���� �����Ǿ� �ֱ� ������
	// ���� �� �ִ� �� �ȿ��� �ݺ��ؼ� ������ �����ϵ��� �Ѵ�

	int size = 0; // ������ ������ ũ��
	int sendsize = 1024; // ������ ������ ���� ũ��
	int totalsize = fsize; // ������ ��ü ũ��

	while (1) { // break ���� �ݺ�
		memcpy(buf, &sendbuf[size], sendsize); // sendbuf�� ������ buf �� sendsize ��ŭ �����Ѵ�
		// buf �� sendsize �� 1KB ��ŭ sendbuf �迭�� ������ ����

		sendsize = sendto(for_send, buf, sendsize, 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // ������ �̹��� ����
		// socket handle ��, ���� ������, ���� ������ ũ��, option, ������ �ּ� ����ü, �ּ� ����ü ũ��
		// sendto �Լ��� ������ ��� sendsize���� �Լ� �� ���� ������ ũ�Ⱑ �� ���̰�
		// ������ ��� SOCKET_ERROR �� ��ȯ�ȴ�

		printf("�۽� ������ ũ�� : %d\n", sendsize); // ���� ������ ũ�� Ȯ��

		if (sendsize == 0) // ���� �����Ͱ� 0 �̸� �ݺ��� Ż��
			break;

		totalsize -= sendsize; // ������ ������ ũ�⸸ŭ ������ ��ü ũ�⸦ ����

		size += sendsize; // ������ ������ ũ�⸸ŭ ������ sendbuf �迭 �� ����

		if (totalsize < sendsize) // ���� ��ü ũ�Ⱑ ���� ũ�⺸�� ���� ���
			sendsize = totalsize; // ���� ũ��� ��ü ũ�Ⱑ �ȴ�
	}
	
	// socket, dll ����
	closesocket(for_send);
	WSACleanup();

	return 0;
}