// tcp����-Ŭ���̾�Ʈ ���� ���� ����
// echo server ��?
// Ŭ���̾�Ʈ�� "hello" ��� ���ڿ��� �۽��ϸ� ������
// "hello"�� ���� �� "hello" ���ڿ��� Ŭ���̾�Ʈ���� �۽���

#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

main(int argc, char * argv[]) {
	// dll �ε�
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // Ŭ���̾�Ʈ���� ���� �Լ� ��� �����ϰ� ������ش�

	// ���� ����
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		printf("socket error\n");
		return -1;
	}

	SOCKADDR_IN SRVAddr; // �ּ� ����ü ����
	// ����(����)�� ������ ���� ���� �޴´�
	memset(&SRVAddr, 0, sizeof(SRVAddr)); // �ּ� ����ü�� �ʱ�ȭ �Ѵ�

	// ���� �����ǿ� ��Ʈ �ּ� ���� �Է�
	SRVAddr.sin_addr.s_addr = inet_addr("172.22.200.48"); // ������ ���� ip �ּ�
	SRVAddr.sin_port = htons(12345); // ������ ���� port number
	SRVAddr.sin_family = AF_INET; // ������ ���� ���

	int errch = 0;
	errch = connect(s, (SOCKADDR*)&SRVAddr, sizeof(SRVAddr)); // connect �Լ��� ���� ���������� ������ �õ��Ѵ�
	if (errch == SOCKET_ERROR) {
		printf("connect error\n");
		return -1;
	}

	// ������ �۽�
	// client ������ ���� ������ ������ ���� �������ش�
	char sendbuf[1024]; // �޽����� ���� �迭 ����
	memset(sendbuf, 0, sizeof(sendbuf)); // �ش� �迭�� 0 ���� �ʱ�ȭ �����ش�

	printf("data input : ");
	scanf("%s", sendbuf); // sendbuf �� ���� ���ڿ��� �����Ѵ� 

	int size;
	size = send(s, sendbuf, strlen(sendbuf), 0); // ���Ͽ� ���� �ڵ鰪, client �� ���� data, cliet ���� data�� ���̰�
	printf("�۽� ������ ũ�� : %d\n", size); // send ��� �Լ��� �����ϰ� �Ǹ� �츮�� ���� data �� ũ�Ⱑ �ǵ��ƿ��� �ȴ�

	// TCP ����� ����� ���� ����̱� ������ �޽����� ���� �������� �Ȱ��� �ǵ��ƿ��� �ȴ�
	// �������� ����� ����� �̷�����ٸ� �������� ������ �޽����� �ǵ����ְ� �ȴ�
	// ����, recv �� ���ڿ��� send �� ���ڿ��� �����ϰ� ������־�� �Ѵ�

	char recvbuf[1024];
	memset(recvbuf, 0, sizeof(recvbuf)); // recv �� ���ڿ� �ʱ�ȭ
	recv(s, recvbuf, sizeof(recvbuf), 0); // recv : data �� �޴� �Լ�
	// recvbuf �� recv �Լ��� ���� ���� �����͸� �����ϰ� �ȴ�
	printf("���� ������ : %s\n", recvbuf); // �츮�� �۽Ź��� �����͸� �� �� Ȯ���ϴ� ����
	// ���´� �����Ͱ� �����ϰ� ���ƿ��°� �����̴�

	// ���� ����
	closesocket(s);

	// dll unload
	WSACleanup();

	return 0;
}