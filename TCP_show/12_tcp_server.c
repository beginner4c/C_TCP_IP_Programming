#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

// server client �� �� ���������� send �� �� ���⿡ �翬�� error �߻��� �´�

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // MAKEWORD �� 2.2 ���� �־��ְ� wsa �� �����Ѵ�

	SOCKET SRVs; // SOCKET ����ü SRVs ����
	SRVs = socket(AF_INET, SOCK_STREAM, 0); // ���� ����
	// AF_INET = ipv4, SOCK_STREAM = TCP, protocol = null(0)

	if (SRVs == INVALID_SOCKET) { // socket�� ����� �������� �ʾ��� ���
		printf("SOCKET ERROR\n");
		return -1;
	}

	SOCKADDR_IN SRVAddr; // �ּҸ� ������ ����ü ���� ����
	memset(&SRVAddr, 0, sizeof(SRVAddr)); // memset = �ʱ�ȭ �۾� �Լ�
	// �ּ�, �ʱ�ȭ ���ϴ� ��, �װͿ� ���� ũ��
	
	int errorCheck;

	// ����ü ���ο� �ִ� ����鿡 ���� �ִ´�
	SRVAddr.sin_family = AF_INET; // IPV4 = AF_INET
	SRVAddr.sin_port = htons(22222); // ��Ʈ ��ȣ�� �־��ش�
	SRVAddr.sin_addr.S_un.S_addr = inet_addr("172.22.200.48"); // inet_addr �Լ��� ���ڿ��� ������ �޾Ƴ���
	// �ּ� �Ҵ�

	errorCheck = bind(SRVs, (struct sockaddr*)&SRVAddr, sizeof(SRVAddr));
	
	if (errorCheck == SOCKET_ERROR) {
		printf("BIND ERROR\n");
		return -1;
	}
	// ���� ����
	errorCheck = listen(SRVs, SOMAXCONN);
	
	if (errorCheck == SOCKET_ERROR) {
		printf("LISTEN ERROR\n");
		return -1;
	}

	//Ŭ���̾�Ʈ ����
	SOCKET CiTs; // CiTs ��� ���� ����
	// Ŭ���̾�Ʈ �ּ� ������ ����ü
	SOCKADDR_IN CiTAddr; // �ּ� ����ü ����
	memset(&CiTAddr, 0, sizeof(CiTAddr)); // �ּ� ����ü�� 0 ���� �ʱ�ȭ
	int CiTLen = sizeof(CiTAddr); // �ּ� ����ü�� ũ��
	//Ŭ���̾�Ʈ ���� ���
	CiTs = accept(SRVs, (struct sockaddr*)(&CiTAddr), &CiTLen);
	
	if (CiTs == INVALID_SOCKET) {
		printf("ACCEPT ERROR\n");
		return -1;
	}

	//Ŭ���̾�Ʈ ������ ����
	char buf[100];
	int recvSize;
	memset(buf, 0, 100); // buf �� 0 ���� �ʱ�ȭ ���ְڴ�
	recvSize = recv(CiTs, buf, sizeof(buf), 0);
	printf("���� ������ : %s\n", buf);
	printf("���� ������ ũ�� : %d\n", recvSize);

	closesocket(SRVs);

	WSACleanup();
	
	return 0;
}