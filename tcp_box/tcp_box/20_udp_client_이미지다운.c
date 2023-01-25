/*
udp �̹��� ���� �ٿ�ε�
Ŭ���̾�Ʈ�� ��θ� �����ϸ� ������ ���Ź��� ��θ� ���ؼ�
�̹��� ������ �о� Ŭ���̾�Ʈ���� �۽�
Ŭ���̾�Ʈ�� ���Ź��� ������ �̹��� ���Ϸ� ����
*/

// ��ó���� ����
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>

int main() {
	// dll �ε�
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // define �� �� MAKEWORD �� ���� ���� ������ wsa �� �־��ش�

	// socket ����
	SOCKET for_send; // socket for_send ����
	for_send = socket(AF_INET, SOCK_DGRAM, 0); // socket�� ipv4, ip protocol, option �־���
	if (for_send == INVALID_SOCKET) { // socket ���� ���� �� ���� ó��
		printf("socket error\n");
		return -1;
	}

	// ������ �۽�
	SOCKADDR_IN SRVaddr; // ������ ���� �ּ� ����ü ����
	memset(&SRVaddr, 0, sizeof(SRVaddr)); // �ּ� ����ü �ʱ�ȭ

	SRVaddr.sin_addr.s_addr = inet_addr("192.168.41.1"); // ������ ip �ּ�
	SRVaddr.sin_port = htons(22222); // ������ ����� ��Ʈ ��ȣ
	SRVaddr.sin_family = AF_INET; // ������ ����� ipv

	// ��� ����
	char path[256]; // ���� ��� ������ ���� �迭
	memset(path, 0, sizeof(path)); // �迭 �ʱ�ȭ
	printf("input path : "); 
	scanf("%s", path); // ���� ��� ������ �Է�
	sendto(for_send, path, sizeof(path), 0, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr)); // ��ġ ������ ������ �۽�
	// socket handle ��, ���� ������, ���� ������ ũ��, option, ������ �ּ� ����ü, �ּ� ����ü ũ��

	SOCKADDR_IN recvaddr; // ������ ������ ������ �ּ� ����ü
	memset((char*)&recvaddr, 0, sizeof(recvaddr)); // �ּ� ����ü �ʱ�ȭ
	int recvlen = sizeof(recvaddr); // �ּ� ����ü ũ�� ����

	// ������ ����
	int datasize = 0; // ���Ͽ� ���� ũ�⸦ ������ ���
	recvfrom(for_send, (char*)&datasize, sizeof(datasize), 0, (SOCKADDR*)&recvaddr, &recvlen); // �����κ��� ũ�� ����
	// socket handle ��, �����͸� ���� ���, ����� ũ��, option, ������ �ּ� ����ü, �ּ� ����ü ũ��
	printf("datasize : %d\n", datasize); // ���Ͽ� ���� ũ�� Ȯ��
	char* recvbuf = (char*)malloc(datasize); // ���Ͽ� ���� �����͸� ������ ���� ���� �Ҵ�
	memset(recvbuf, 0, datasize); // �����Ҵ� ���� �ʱ�ȭ

	// ��뷮 ���Ͽ� �ݺ��� ����
	char buf[1024]; // �ݺ��ؼ� ������ �迭 ����
	memset(buf, 0, sizeof(buf)); // �迭 �ʱ�ȭ
	int totalbuf = 0; // ������ ������ ��ü ũ��
	int recvsize = 0; // ������ ������ ũ��

	while (1) { // break ���� ������ �ݺ�
		recvsize = recvfrom(for_send, buf, sizeof(buf), 0, (SOCKADDR*)&recvaddr, &recvlen); // �����κ��� ������ ����
		// recvsize���� ������ buf �� ũ�Ⱑ ����ȴ�
		if (recvsize == 0) // ������ ũ�Ⱑ 0 �� �� break
			break;
		printf("���� : %d\n", recvsize); // ������ ������ ũ�� Ȯ��
		memcpy(&recvbuf[totalbuf], buf, recvsize); // ������ �����͸� recvbuf �� ������ ũ�� ��ŭ ����
		totalbuf += recvsize; // ������ ������ ��ü ũ�⿡ ������ ������ ũ�� ������
	}

	// ������ �����͸� ���Ϸ� ����
	FILE* fp; // FILE ����
	fp = fopen("C:\\Users\\asus\\Downloads\\udp_down_test2.png", "wb"); // ���� ��ġ ����, ���� ���
	fwrite(recvbuf, datasize, 1, fp); // recvbuf�� �����͸� datasize ��ŭ �� �� �ݺ��ؼ� fp �� �����Ѵ�
	fclose(fp); // ���� ����

	// socket, dll ����
	closesocket(for_send);
	WSACleanup();

	return 0;
}