#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // �ɼ� ���� �� �ʿ� ���
#pragma comment(lib, "ws2_32.lib")

// MULTICAST ��� => �� �� �ټ��� ��� ���

int main() {
	WSADATA wsa; // dll �ε�
	WSAStartup(MAKEWORD(2, 2), &wsa); // ���� Ȯ��

	// udp ���� ����
	SOCKET mulsock = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, udp, option
	if (mulsock == INVALID_SOCKET) { // ���� ���� Ȯ��
		printf("SOCKET ERROR!\n");
		return -1;
	}

	// �ּ� ����
	SOCKADDR_IN srvaddr; // �ּ� ����ü ����
	memset(&srvaddr, 0, sizeof(srvaddr)); // �ּ� ����ü �ʱ�ȭ
	
	srvaddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // ip �ּ�
	srvaddr.sin_family = AF_INET; // ip version 4
	srvaddr.sin_port = htons(12345); // port ��ȣ

	int errch = 0; // bind error check
	errch = bind(mulsock, (SOCKADDR*)&srvaddr, sizeof(srvaddr)); // os�� �㰡 ����
	// socket handle ��, �ּ� ����ü, �ּ� ����ü ũ��
	if (errch == SOCKET_ERROR) { // bind �Լ� ���� Ȯ��
		printf("bind error\n");
		return -1;
	}

	// ��Ƽĳ��Ʈ ����
	struct ip_mreq MR; // ��Ƽĳ��Ʈ ���Կ� �ּ� ����ü
	MR.imr_interface.s_addr = inet_addr("192.168.41.1"); // local �ּҸ� �Է�
	MR.imr_multiaddr.s_addr = inet_addr("224.2.2.2"); // multicast �� ���� �ּҸ� ���� �Է�

	setsockopt(mulsock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&MR, sizeof(MR)); // IP_ADD_MEMBERSHIP���� ����
	// socket handle ��, LEVLE ��, OPTION ��, ��Ƽĳ��Ʈ �ּ� ����ü, �ּ� ����ü ũ��

	// ������ ����
	char recvbuf[1024]; // �����͸� ������ ����
	memset(recvbuf, 0, sizeof(recvbuf)); // ���� �ʱ�ȭ
	
	SOCKADDR_IN cltaddr; // ��� �ּҸ� ���� �ּ� ����ü
	int cltlen = sizeof(cltaddr); // �ּ� ����ü ũ�� ����
	memset(&cltaddr, 0, cltlen); // �ּ� ����ü �ʱ�ȭ

	int recvlen = 0; // ���� ������ ũ�� Ȯ�ο� ����
	recvlen = recvfrom(mulsock, recvbuf, sizeof(recvbuf), 0, (SOCKADDR*)&cltaddr, &cltlen); // ������ ����
	// socket handle ��, ������ ���� ����, ���� ���� ũ��, option, ������ �ּ� ����ü, �ּ� ����ü ũ��
	printf("���� ������ ũ�� : %d\n", recvlen); // recvfrom �Լ��� ���� ũ�� Ȯ��
	printf("���� ������ : %s\n", recvbuf); // ���� ������ Ȯ��

	// ��Ƽĳ��Ʈ Ż��
	setsockopt(mulsock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&MR, sizeof(MR)); // IP_DROP_MEMBERSHIP���� Ż��

	// socket, dll ����
	closesocket(mulsock);
	WSACleanup();

	return 0;
}