/*
time_t �ڷ���, struct tm �ڷ���, localtime() �Լ�, time() �Լ��� ���ؼ�
�˾ƺ��� ������ ������ �ð��� Ŭ���̾�Ʈ�� ���� �� ���(�ð������� ������)
*/

// ��ó���� ���� 
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>
#include<time.h>

int main() {
	// winsock ����
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // define �� �� MAKEWORD �� ���� ���� ������ wsa �� �־��ش�

	// socket ����
	SOCKET UDPs;
	UDPs = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, udp, protocol
	if (UDPs == INVALID_SOCKET) { // socket ���� ���� �߻� �� ���� ó��
		printf("SOCKET ERROR!\N");
		return -1;
	}

	// ������ �ּ� ����ü
	SOCKADDR_IN SRVaddr; // �ּ� ����ü ����
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // ������ ip �ּ�
	SRVaddr.sin_port = htons(22222); // ������ ����� ��Ʈ ��ȣ
	SRVaddr.sin_family = AF_INET; // ������ ����� ipv

	// �ּ� ����
	int error = 0;
	error = bind(UDPs, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // bind �Լ��� ���� os�� ����� ��´�
	if (error == SOCKET_ERROR) { // bind �Լ� ���� �� ���� ó��
		printf("BIND ERROR\n");
		return -1;
	}

	// ������ ����
	SOCKADDR_IN CLTaddr; // client �� ������ ���� �ּ� ����ü ����
	int CLTlen = sizeof(CLTaddr); // �ּ� ����ü�� ũ��
	memset((char*)&CLTaddr, 0, CLTlen); // �ּ� ����ü �ʱ�ȭ

	char msg[256]; // Ŭ���̾�Ʈ�� �޽����� �޾� ������ ��
	memset(msg, 0, sizeof(msg)); // ������ ��� �ʱ�ȭ

	recvfrom(UDPs, msg, sizeof(msg), 0, (SOCKADDR*)&CLTaddr, &CLTlen); // client�� ���� ������ ����
	// socket handle ��, ������ ���, ������ ����� ũ��, option, client �ּҸ� ���� �ּ� ����ü, �ּ� ����ü ũ��
	
	// �۽��� �ð� ���
	time_t tm; // long Ÿ�� ����ü �ڷ��� time_t
	time(&tm); // time �̶�� �Լ��� ��������� �� ���� ������ �ð��� �� ������ tm �� ����
	struct tm * lt = localtime(&tm); // localtime �Լ��� ���� time.h �� ���ǵ� ����ü tm �� �����͸� �־��ش�;
	// tm ���� �� ������ ������ �Ǿ��ֱ� ������ localtime �Լ��� ����ؼ� ����ü�� �����ϴ°� �ٶ����ϴ�

	char time_send[512]; // time_send �迭 ����
	memset(time_send, 0, sizeof(time_send)); // �迭 �ʱ�ȭ

	sprintf(time_send, "������ %d�� %d�� %d�� ����ð��� %d�� %d�� �Դϴ�.\n",
		lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min);

	sendto(UDPs, time_send, strlen(time_send), 0, (SOCKADDR*)&CLTaddr, CLTlen); // client�� ������ ����
	// socket, ���� ������, ������ ũ��, option, client �ּ� ����ü, �ּ� ����ü ũ��

	printf("�ð� %d�� %d�� %d�� %d�� %d�� �� �����߽��ϴ�.\n",
		lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min);

	// socket, winsock ����
	closesocket(UDPs);
	WSACleanup();

	return 0;
}