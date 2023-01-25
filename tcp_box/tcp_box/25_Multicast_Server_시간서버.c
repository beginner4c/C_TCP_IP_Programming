// IPPROTO_IP �� �̿��� �ð� ���� ���α׷��� �ۼ�
// Sender �� Receiver �� ���� ����
// Sender �� ���� �ð��� Receiver�鿡�� 1 �� �������� ����
// Receiver �� ���� ������ ���� �ð��� 1 �� �������� ���

// Sender �ð� ����

#include<winsock2.h>
#include<stdio.h>
#include<time.h>
#include<ws2tcpip.h> // �ɼ� ���� �� �ʿ� ���
#pragma comment(lib, "ws2_32.lib")

// MULTICAST ��� => �� �� �ټ��� ��� ���

int main() {

	// dll �ε�
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp ���� ����
	SOCKET mulsock = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, socket dataGRAM, option
	if (mulsock == INVALID_SOCKET) { // ���� �� ���� ó��
		printf("SOCKET ERROR!\n");
		return -1;
	}

	// ��Ƽĳ��Ʈ TTL ��
	int multtl = 64; // ������ ttl �� ����
	setsockopt(mulsock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&multtl, sizeof(multtl)); // ttl �� ����
	// socket handle ��, level ��, option ��, char ���� ttl ��, ttl �� ũ��

	// ������ �۽�
	SOCKADDR_IN srvaddr; // �ּ� ����ü ����
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_addr.s_addr = inet_addr("233.3.3.3"); // ip address
	srvaddr.sin_port = htons(12345); // port ��ȣ
	srvaddr.sin_family = AF_INET; // ip version 4

	char sendbuf[1024]; // ���� �����͸� ������ ����
	memset(sendbuf, 0, sizeof(sendbuf)); // ������ ���� 0 ���� �ʱ�ȭ
	time_t tm; // �ð��� ���� ����ü ����
	struct tm* lt; // localtime �� �����ϱ� ���� ����ü ����
	int sendsize = 0; // sendto �Լ��� ����� ���� ������ ũ�⸦ Ȯ���� ���� ����
	int i = 0; // while ���� ���� ���ǿ� ����

	while (i < 10) { // i �� 10 ���� ���� ���� �ݺ�
		time(&tm); // time �Լ��� ��������� �� ���� ������ �� ������ tm�� ����
		lt = localtime(&tm); // localtime �Լ��� ���� �� ������ �ð��� ����Ͻú��� �� ��ȯ�ߴ�
		sprintf(sendbuf, "%d�� %d�� %d�� %d�� %d�� %d��\n",
			lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
		// sendbuf ������ �����͸� �����Ѵ�
		sendto(mulsock, sendbuf, strlen(sendbuf), 0, (SOCKADDR*)&srvaddr, sizeof(srvaddr)); // ������ ����
		printf("%d�� ����\n", i + 1); // ���۵� Ƚ�� Ȯ��
		i++; // ���ǿ� i ����
		Sleep(1000); // 1 �� ���� ����
	}
	// printf("�۽� ������ ũ�� : %d\n", sendsize);
	// ������ ũ�� Ȯ�� �� ���

	// socket dll ����
	closesocket(mulsock);
	WSACleanup();

	return 0;
}