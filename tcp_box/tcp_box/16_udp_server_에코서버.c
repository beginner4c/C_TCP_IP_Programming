// UDP ���� ���� - ���� ����

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

int main() {
	WSADATA wsa;
	// winsock dll �ε�
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// ���� ����
	SOCKET s;
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET) { // ���� ���� ���� �� ���� ó��
		printf("socket error!\n");
		return -1;
	}

	// �ּ� ����
	// struct sockaddr_in
	SOCKADDR_IN SRVaddr; // �ּ� ����ü ���� ����
	memset(&SRVaddr, 0, sizeof(SRVaddr));

	SRVaddr.sin_family = AF_INET; // ipv4 ���
	SRVaddr.sin_port = htons(12345); // ��Ʈ ��ȣ �Է�
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.1.1"); // server �� ���� ip �ּ�
	// SRVaddr.sin_addr.S_un.S_addr = ���� �������ּ�;

	int errch = 0;
	errch = bind(s, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind �Լ��� ���� os�� ����޴´�
	if (errch == SOCKET_ERROR) { // bind ���� �� ���� ó��
		printf("bind error!\n"); // ���� ���� �����Ǹ� �߸� ���� ��� �߻��Ѵ�
		return -1;
	}

	// ������ ����
	char buf[1024]; // recvbuf��� 1MB ���� ����
	memset(buf, 0, sizeof(buf)); // recvbuf �ʱ�ȭ

	SOCKADDR_IN CLTaddr; // �ּ� ����ü ���� ���� (recvfrom �Լ��� ����ϱ� ����)
	int CLTlen = sizeof(CLTaddr); // �ּ� ����ü ũ�� CLTlen �� ����
	memset(&CLTaddr, 0, CLTlen); // �ּ� ����ü�� 0 ���� �ʱ�ȭ

	int recvlen = 0;
	recvlen = recvfrom(s, buf, sizeof(buf), 0, (SOCKADDR*)&CLTaddr, &CLTlen);
	// recvfrom ���ڰ�(SOCKET, ������ ����, ������ ������ ũ��, �ɼ� ��, Ŭ���̾�Ʈ ���� ���� ����ü, ������ ũ�⿡ ���� �ּ�)
	// recvlen ���� recvfrom �� ���� ���� �������� ũ�Ⱑ ����
	// recvfrom �� ���� buf ���� ���� �����Ͱ� ����ǰ� CLTaddr ���� Ŭ���̾�Ʈ�� ������ ����ȴ�
	printf("���ŵ����� : %s\n", buf); // ���� ������ Ȯ��

	printf("������ �Է� : "); // �ٽ� Ŭ���̾�Ʈ�� ���� ������
	gets_s(buf, sizeof(buf));
	sendto(s, buf, strlen(buf), 0, (SOCKADDR*)&CLTaddr, sizeof(CLTaddr));

	// ���� ���� �� dll ��ε�
	closesocket(s);
	WSACleanup();

	return 0;
}