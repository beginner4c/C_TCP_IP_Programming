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
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp ���� ����
	SOCKET mulsock = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, socket dataGRAM, option
	if (mulsock == INVALID_SOCKET) { // ���� �� ���� ó��
		printf("SOCKET ERROR!\n");
		return -1;
	}

	// ��Ƽĳ��Ʈ TTL ��
	int multtl = 32; // ������ ttl �� ����
	setsockopt(mulsock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&multtl, sizeof(multtl)); // ttl �� ����
	// socket handle ��, level ��, option ��, char ���� ttl ��, ttl �� ũ��

	// ����� ����� �ּ� ����ü
	SOCKADDR_IN sendaddr; // �ּ� ����ü ����
	memset(&sendaddr, 0, sizeof(sendaddr));

	sendaddr.sin_addr.s_addr = inet_addr("233.3.3.3"); // ip address
	sendaddr.sin_port = htons(22222); // port ��ȣ
	sendaddr.sin_family = AF_INET; // ip version

	// ������ ����
	int error = 0; // sendto function error check
	_msg msg; // �����͸� ������ ����ü ����
	memset(&msg, 0, sizeof(msg)); // ����ü �ʱ�ȭ
	sprintf(msg.q_str, "[����] �ڽ��� ��ȣ�ϴ� ���δ�?\n1.���α׷���\n2.��Ʈ��ũ ������\n3.�ý��� ������\n4. �������� ������");
	// ����ü ���ο� ���� ������ ����
	printf("%s", msg.q_str); // ������ ���� Ȯ��

	error = sendto(mulsock, (char*)&msg, sizeof(msg), 0, (SOCKADDR*)&sendaddr, sizeof(sendaddr)); // ������ ����
	// socket handle ��, ���� ������, �������� ũ��, option, ����� �ּ� ����ü, �ּ� ����ü ũ��
	if (error == SOCKET_ERROR) { // sendto error �߻� �� ���� ó��
		printf("SENDTO FUNCTION ERROR\n");
		return -1;
	}

	// ��� ��� �ּ� ����ü
	SOCKADDR_IN recvaddr; // ������ �ּҸ� ������ ����ü
	int recvlen = sizeof(recvaddr); // �ּ� ����ü ũ�� ����

	// ������ ����
	int total[5]; // �����͸� ���� ����
	memset(total, 0, sizeof(total)); // ���� �ʱ�ȭ

	printf("\n### ���� ���� ��� ###\n");

	int rcvtime = 5000; // receive time out �� ���� => 5 �� ���ȸ� ������ ��ٸ��� �ȿ��� ����
	setsockopt(mulsock, SOL_SOCKET, SO_RCVTIMEO, (char*)&rcvtime, sizeof(rcvtime));
	// socket handle ��, level ��, option ��, char ������ timeout ������, �������� ũ��

	while (1) // break ������ ������ �ݺ�
	{
		error = recvfrom(mulsock, (char*)&msg, sizeof(msg), 0, (SOCKADDR*)&recvaddr, &recvlen);
		if (error == SOCKET_ERROR) // �߸��� ���� Ȥ�� time out �߻� �� break
			break;

		if (msg.a_num >= 1 && msg.a_num <= 4) { // ���Ű� Ȯ�� ��
			total[msg.a_num]++; // ������ ���� ������ ����
		}
	}

	// ���� ���� ���� ��
	for (int i = 1; i < 5; i++)
		printf("%d�� : %d��\n", i, total[i]); // ����� ���

	// socket dll ����
	closesocket(mulsock);
	WSACleanup();

	return 0;
}