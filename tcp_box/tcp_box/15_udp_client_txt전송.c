/*UDP Ŭ���̾�Ʈ���� ������ �ϳ� ����� �����͸� �־�
������ �� ������ ������ �о� UDP �������� ����,
������ ���� �����͸� ���Ͽ� �����Ѵ�*/
// define �� ������ F12 Ű�� ���ؼ� Ȯ���� �����ϴ�

// ��ó���� ����
#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main() {
	// winsock dll �ε�
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	// define�� ������ F12 ���� ���ؼ� Ȯ���� �����ϴ�
	// define�� ������ Ȯ�� �Ŀ��� ctrl + F4 �� ���ؼ� �ش� ȭ���� ������ �� �ִ�

	// socket ����
	SOCKET s; // ���� ������ �ڷ��� SOCKET
	// s �� �ڵ鰪(== �����ΰ��� ������ �� �ִ� ��)
	s = socket(AF_INET, SOCK_DGRAM, 0); // IPv4, UDP, �������� �ɼ�
	// AF_INET�� SOCK_DGRAM�� 2�� define�� ���̴�
	if (s == INVALID_SOCKET) { // ����ó���� ���� s �� ����� �� ���� ���� ���� ��츦 Ȯ���Ѵ�
		printf("socket error");
		return -1;
	}

	// ������ �۽�
	SOCKADDR_IN SRVaddr; // IP �ּ�, ��Ʈ ��ȣ, IPv �� �־��� ����ü ����
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // SRVaddr ����ü�� 0���� �ʱ�ȭ

	// ������ ���� ������ SRVaddr �� �־��ش�
	SRVaddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // ����ü�� ���� �� ip �Է�
	// SRVaddr.sin_addr.S_un.S_addr == SRVaddr.sin_addr.s_addr (���� �����ϴ�)
	// s_addr �� S_un.S_addr �� define �� ���̴�
	SRVaddr.sin_port = htons(12345); // ������ ������ ��Ʈ ��ȣ �Է�
	// �Ϲ������� ����ϴ� intel cpu �� ��� littel endian ���������
	// network programming ������ big endian ����� ����ϱ� ������ htons�� �ʿ��ϴ�
	SRVaddr.sin_family = AF_INET; // ipv4 ���� ipv6 ���� �־��ش� 
	// ipv4 = AF_INET = 2, ipv6 = AF_INET6 = 23

	FILE* fp;
	fp = fopen("C:\\Users\\asus\\Downloads", "rb"); // �о�� ������ ��ġ, 
	// r = rt (1 byte �� �о�´�), w = wt (1 byte �� �᳻����)
	// ��뷮�� �ű� ���� rb Ȥ�� wb �� ����Ѵ� (read binary or write binary)
	if (fp == NULL) {
		printf("������ ã�� �� �����ϴ�");
		return -1;
	}
	fseek(fp, 0, SEEK_END); // fp �� Ŀ���� �� �κ����� �̵����Ѽ� 0 ��ŭ �̵�
	// fseek(fp, -5, SEEK_END) �� ��� Ŀ���� ������ �������� 5 ĭ �̵����� ��ġ��Ų��
	int fsize = ftell(fp); // ftell�� ���� fp �� Ŀ�� ��ġ������ ũ�⸦ ���ͼ� fsize�� �����Ѵ�

	char* sendbuf = (char*)malloc(fsize); // fsize ũ�⸸ŭ heap ������ ũ�� �Ҵ�
	memset(sendbuf, 0, fsize); // sendbuf �� ������ fsize ũ�⸸ŭ 0 ���� ä���ִ´�

	fseek(fp, 0, SEEK_SET); // fp �� Ŀ���� �ٽ� ù �κ����� �̵����� 0 ��ŭ �̵�
	fread(sendbuf, 1, fsize, fp); // sendbuf �� 1byte �� fsize ũ�⸸ŭ fp �� �о� �Ű��ְڴ�
	fclose(fp);
	// printf("sendbuf : %s\n", sendbuf); �� ������� �� �� ���� �̻��� ���� ������ ������
	// %s �� NULL ������ �дµ� ������ ������ NULL ���� �ƴ� EOF �� �ֱ� �����̴�
	// �ذ� ������� malloc �� fsize + 1 �Ҵ� �� sendbuf[fsize] �� NULL�� �ִ´�

	int sendsize = 0;
	sendsize = sendto(s, sendbuf, fsize, 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr));
	// sendto �Լ��� return ���� int �̰� �ʿ��� ������
	// SOCKET, ���� �����͸� ���� �ּ�, ���� ũ��, �ɼ� ��, ������ ���� �ּ� ����ü ����, �ּ� ����ü ���� ũ��
	printf("�۽� ������ ũ�� : %d\n", sendsize); // �ƹ��� �������� �������� ��� ��µǴ� �޽���

	// ���� ����
	closesocket(s);

	// dll ��ε�
	WSACleanup();

	return 0;
}