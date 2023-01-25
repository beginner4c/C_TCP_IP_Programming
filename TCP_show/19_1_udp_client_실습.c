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

	// socket ����
	SOCKET s;
	s = socket(AF_INET, SOCK_DGRAM, 0); // IPv4, UDP, �������� �ɼ�
	// AF_INET�� SOCK_DGRAM�� 2�� define�� ���̴�
	if (s == INVALID_SOCKET) {
		printf("socket error");
		return -1;
	}

	// ������ �۽�
	SOCKADDR_IN SRVaddr; // IP �ּ�, ��Ʈ ��ȣ, IPv �� �־��� ����ü ����
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // ����ü �ʱ�ȭ

	SRVaddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // ����ü�� ���� �� ip �Է�
	SRVaddr.sin_port = htons(12345); // ������ ������ ��Ʈ ��ȣ �Է�
	SRVaddr.sin_family = AF_INET; // ipv4 ���� ipv6 ���� �־��ش� 

	FILE* fp;
	fp = fopen("c:\\Data.txt", "rb");
	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);

}