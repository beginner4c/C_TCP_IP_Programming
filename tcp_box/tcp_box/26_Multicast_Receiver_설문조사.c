// IPPROTO_IP�� �̿��� �������� ���α׷� �ۼ�
// sender�� receiver ���� ����
// sender�� ���� ������ ���ڿ��� receiver�鿡�� ����
// receiver�� ���� ������ ȭ�鿡 ��� �� �Է� ���� sender���� ����ĳ��Ʈ ����
// sender�� receiver���� �Է� ���� �ٽ� ���


#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // �ɼ� ���� �� �ʿ� ���
#pragma comment(lib, "ws2_32.lib")

// MULTICAST ��� => �� �� �ټ��� ��� ���

typedef struct msg {
	int a_num;
	char q_str[512];
}_msg;

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
	srvaddr.sin_port = htons(22222); // port ��ȣ

	int errch = 0; // bind error check
	errch = bind(mulsock, (SOCKADDR*)&srvaddr, sizeof(srvaddr)); // os�� �㰡 ����
	// socket handle ��, �ּ� ����ü, �ּ� ����ü ũ��
	if (errch == SOCKET_ERROR) { // bind �Լ� ���� Ȯ��
		printf("bind error\n");
		return -1;
	}

	// ��Ƽĳ��Ʈ ����
	struct ip_mreq mr; // ��Ƽĳ��Ʈ ���Կ� �ּ� ����ü
	mr.imr_interface.s_addr = inet_addr("192.168.41.1"); // local �ּҸ� �Է�
	mr.imr_multiaddr.s_addr = inet_addr("233.3.3.3"); // multicast �� ���� �ּҸ� ���� �Է�

	setsockopt(mulsock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mr, sizeof(mr)); // IP_ADD_MEMBERSHIP���� ����
	// socket handle ��, LEVLE ��, OPTION ��, ��Ƽĳ��Ʈ �ּ� ����ü, �ּ� ����ü ũ��

	SOCKADDR_IN recvaddr; // ��� �ּҸ� ���� �ּ� ����ü
	int recvlen = sizeof(recvaddr); // �ּ� ����ü ũ�� ����
	memset(&recvaddr, 0, recvlen); // �ּ� ����ü �ʱ�ȭ

	// ������ ����
	_msg msg; // ������ ���� ����ü ����
	memset((char*)&msg, 0, sizeof(msg)); // ����ü �ʱ�ȭ

	errch = recvfrom(mulsock, (char*)&msg, sizeof(msg), 0, (SOCKADDR*)&recvaddr, &recvlen); // ������ ����
	// socket handle ��, ������ ���� ����, ���� ���� ũ��, option, ��� �ּ� ���� ����ü, �ּ� ����ü ũ��
	if (errch == SOCKET_ERROR) { // ���� ���� �� ���� ó��
		printf("RECEIVEFROM FUNCTION ERROR\n");
		return -1;
	}

	printf("%s", msg.q_str); // ���� ������ ���
	printf("\n�亯 �Է�(1-4 : "); // ���
	int an = 0;
	scanf("%d", &an); // ������ �Է�

	memset((char*)&msg, 0, sizeof(msg)); // �����͸� �޾Ҵ� ����ü �ʱ�ȭ
	msg.a_num = an; // ����ü�� �Էµ� ������ ����

	errch = sendto(mulsock, (char*)&msg, sizeof(msg), 0, (SOCKADDR*)&recvaddr, recvlen); // ������ �۽�
	// socket handle ��, ���� ������ ����ü, ����ü ũ��, option, ���� �ּ� ����ü, �ּ� ����ü ũ��
	if (errch == SOCKET_ERROR) { // ���� ���� �� ���� ó��
		printf("SENDTO FUNCTION ERROR\n");
		return -1;
	}

	// ��Ƽĳ��Ʈ �׷� Ż��
	setsockopt(mulsock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mr, sizeof(mr));

	// socket dll ����
	closesocket(mulsock);
	WSACleanup();

	return 0;
}