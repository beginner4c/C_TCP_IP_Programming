/*
time_t �ڷ���, struct tm �ڷ���, localtime() �Լ�, time() �Լ��� ���ؼ�
�˾ƺ��� ������ ������ �ð��� Ŭ���̾�Ʈ�� ���� �� ���(�ð������� ������)
*/

// ��ó���� ���� 
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>

int main() {
	// winsock ����
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // define �� �� MAKEWORD �� ���� ���� ������ wsa �� �־��ش�

	// socket ����
	SOCKET UDPc;
	UDPc = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, udp, protocol
	if (UDPc == INVALID_SOCKET) { // socket ���� ���� �߻� �� ���� ó��
		printf("SOCKET ERROR!\N");
		return -1;
	}

	// ����� ������ �ּ� ����ü
	SOCKADDR_IN sendAddr; // �ּ� ����ü ����
	sendAddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // ������ ip �ּ�
	sendAddr.sin_port = htons(22222); // ������ ����� ��Ʈ ��ȣ
	sendAddr.sin_family = AF_INET; // ������ ����� ipv

	char msg[256] = "�ð� ���� ��û�մϴ�."; // �������� ���� �޽���

	sendto(UDPc, msg, strlen(msg), 0, (SOCKADDR*)&sendAddr, sizeof(sendAddr)); // ������ ������ ����
	// socket handle ��, ���� data, ���� data ����, option, ������ �ּ� ����ü, �ּ� ����ü ũ��

	char time[512]; // �������� ���� �����͸� ������ ��
	memset(time, 0, sizeof(time)); // ������� 0���� �ʱ�ȭ

	SOCKADDR_IN recvAddr; // ������ �ּҸ� ���� �ּ� ����ü
	int recvLen = sizeof(recvAddr); // �ּ� ����ü�� ũ��
	memset((char*)&recvAddr, 0, recvLen); // �ּ� ����ü �ʱ�ȭ

	recvfrom(UDPc, time, sizeof(time), 0, (SOCKADDR*)&recvAddr, &recvLen); // �����κ��� ������ ����
	// socket handle ��, ���� ���, �޴� ����� ũ��, option, ���� ������ ���� �ּ� ����ü, �ּ� ����ü ũ��

	printf("%s\n", time); // �� �޾Ҵ��� Ȯ�� �� ���

	// socket, winsock ����
	closesocket(UDPc);
	WSACleanup();

	return 0;
}