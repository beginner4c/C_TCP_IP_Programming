#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // �ɼ� ���� �� �ʿ� ���
#pragma comment(lib, "ws2_32.lib")

// MULTICAST ��� => �� �� �ټ��� ��� ���

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp ���� ����
	SOCKET mulsock = socket(AF_INET, SOCK_DGRAM, 0);
	if (mulsock == INVALID_SOCKET) {
		printf("SOCKET ERROR!\n");
		return -1;
	}
	
	// �ּ� ����ü
	SOCKADDR_IN muladdr;
	memset(&muladdr, 0, sizeof(muladdr));

	muladdr.sin_addr.s_addr = inet_addr("192.168.41.1");
	muladdr.sin_family = AF_INET;
	muladdr.sin_port = htons(33333);

	int error;
	error = bind(mulsock, (SOCKADDR*)&muladdr, sizeof(muladdr));
	// bind(socket handle ��, �ּ� ����ü, �ּ� ����ü ũ��)
	if (error == SOCKET_ERROR) {
		printf("bind error\n");
		return -1;
	}

	// ��Ƽĳ��Ʈ �ּ� ����ü
	struct ip_mreq Mreq;
	Mreq.imr_interface.s_addr = inet_addr("192.168.41.1"); // local�� ���� �ּҸ� ���� �� �ִ� ����
	Mreq.imr_multiaddr.s_addr = inet_addr("233.3.3.3"); // ��Ƽĳ��Ʈ�� ���� �ּҸ� ���� �� �ִ� ����

	// ��Ƽ ĳ��Ʈ ����
	setsockopt(mulsock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&Mreq, sizeof(Mreq)); // IP_ADD_MEMBERSHIP = ���
	// socket handle ��, level ��, ������ option ��, ��ϵ� �ּ� ����ü, �ּ� ����ü ũ��
	// setsockopt �� ������ �Ǹ� Mreq.imr_multiaddr �� ���� local ���� �޾ƺ� �� �ְ� �ȴ�

	// ������ ����
	char rcvbuf[512] = "\0"; // �޽����� ���� ����
	recvfrom(mulsock, rcvbuf, sizeof(rcvbuf), 0, NULL, NULL); // �޽��� ����
	// socket handle ��, �����͸� ������ ����, �ش� ������ ũ��, option, �ּ� ����ü, �ּ� ����ü ũ��
	// recvfrom ���� NULL ���� ����� ������ �̹� multicast�� �����߱� ������ ��� �ּҸ� �ȴٰ� �Ǵ��߱� �����̴�
	printf("��Ƽ ������ : %s\n", rcvbuf);

	// ��Ƽĳ��Ʈ Ż�� -> ������ ������ ���� �����ٸ� Ż���Ѵ�
	setsockopt(mulsock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&Mreq, sizeof(Mreq)); // IP_DROP_MEMBERSHIP = Ż��
	// socket handle ��, level ��, ������ option ��, Ż���� �ּ� ����ü, �ּ� ����ü ũ��

	closesocket(mulsock);
	WSACleanup();

	return 0;
}