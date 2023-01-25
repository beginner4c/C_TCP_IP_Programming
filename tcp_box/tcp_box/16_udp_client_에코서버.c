// UDP ���� ���� - Ŭ���̾�Ʈ ����

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
	
	char buf[512] = { 0 };
	printf("������ �Է� : ");
	gets_s(buf, sizeof(buf));
	int sendsize = 0;
	sendsize = sendto(s, buf, sizeof(buf), 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr));
	// sendto �Լ��� return ���� int �̰� �ʿ��� ������
	// SOCKET, ���� �����͸� ���� �ּ�, ���� ũ��, �ɼ� ��, ������ ���� �ּ� ����ü ����, �ּ� ����ü ���� ũ��
	
	char new_buf[512] = { 0 };
	recvfrom(s, new_buf, sizeof(new_buf), 0, 0, 0); // ������ ������ �̹� �ֱ� ������ ���� ����ü�� ���� �ʴ´�
	printf("�۽� ������ : %s\n", new_buf); // �ƹ��� �������� �������� ��� ��µǴ� �޽���

	// ���� ����
	closesocket(s);
	// dll ��ε�
	WSACleanup();

	return 0;
}