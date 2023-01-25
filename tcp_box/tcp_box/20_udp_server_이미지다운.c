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

	// ��� ����� �ּ� ����ü
	SOCKADDR_IN recvaddr; // �ּ� ����ü ����
	int recvlen = sizeof(recvaddr); // �ּ� ����ü ũ�� ����

	char path[256]; // ��θ� ������ �迭 ����
	memset(path, 0, sizeof(path)); // �迭 �ʱ�ȭ
	recvfrom(UDPs, path, sizeof(path), 0, (SOCKADDR*)&recvaddr, &recvlen); // client�� ���� ��� ���� ����
	// socket handle ��, ������ �迭, �迭�� ũ��, option, ������ �ּ� ����ü, �ּ� ����ü ũ��
	printf("��� : %s\n", path); // ���Ȯ��

	// ������ ����
	FILE* fp; // FILE ����
	fp = fopen(path, "rb"); // ������ ���, �б� ���
	fseek(fp, 0, SEEK_END); // fp �� Ŀ�� ��ġ�� ���� ������ 0 ��ŭ �̵�
	int datasize = ftell(fp); // fp �� Ŀ�� ��ġ���� ũ�⸦ ����
	fclose(fp); // ���� ����

	sendto(UDPs, (char*)datasize, sizeof(datasize), 0, (SOCKADDR*)&recvaddr, recvlen); // client �� ������ �۽�
	// socket handle ��, ���� ������, ������ ũ��, option, client �ּ� ����ü, �ּ� ����ü ũ��

	char* sendbuf = (char*)malloc(datasize); // ���� ������ ũ�⸸ŭ �����Ҵ� ���� ����
	memset(sendbuf, 0, datasize); // �����Ҵ� ���� �ʱ�ȭ

	fp = fopen(path, "rb"); // ������ ���, �б� ���
	fread(sendbuf, datasize, 1, fp); // sendbuf �� datasize ��ŭ �� �� �ݺ��ؼ� fp�� �����͸� ����
	fclose(fp); // ���� ����

	char udpbuf[1024]; // ���� �����͸� ���� �迭 ����
	memset(udpbuf, 0, sizeof(udpbuf)); // �迭 �ʱ�ȭ
	int sendsize = sizeof(udpbuf); // ���� ������ ũ��
	int totalsize = 0; // ���� �������� �� ũ��
	printf("%d\n", datasize); // ���� ������ ũ�� Ȯ��
	int size = 0; // ���� ������ ũ��

	while (1) { // break �� ���� ������ �ݺ�
		memcpy(udpbuf, &sendbuf[totalsize], sendsize); // udpbuf �� sendbuf �� sendsize ��ŭ ������ ����
		// heap ������ ����� �����͸� �迭�� �ٽ� �����Ѵ�
		size = sendto(UDPs, udpbuf, sendsize, 0, (SOCKADDR*)&recvaddr, recvlen); // �迭�� �����͸� client�� ����
		// socket handle ��, ���� ������, ���� ������ ũ��, option, client �ּ� ����ü, �ּ� ����ü ũ��

		if (size == 0) // ���� �����Ͱ� 0 �� ��� break;
			break;

		datasize -= size; // ���� ������ �ϴ� ������ ũ�⿡�� ���� �����͸� ����

		if (datasize < size) // ���� �������ϴ� ������ ũ�Ⱑ ���� ������ ���� ���� ���
			sendsize = datasize; // ���� ������ ũ��� ���� ������ ũ��� �ٲ۴�

		totalsize += size; // ���� �������� �� ũ��� ���� �����͸�ŭ �����ش�

		printf("���� ������ : %d\n", size); // ���� ������ ũ�� Ȯ��
	}

	// socket dll ����
	closesocket(UDPs);
	WSACleanup();

	return 0;
}