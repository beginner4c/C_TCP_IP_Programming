// tcp �������� ������ Ŭ���̾�Ʈ�� ip/port �ּҸ� ����Ͻÿ�
#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa); // ���Ͽ� ���� �Լ��� ����� �� �ְ� ������ش�
	
	SOCKET s;
	s = socket(AF_INET,SOCK_STREAM, 0); // ���� ����

	if (s == INVALID_SOCKET) {
		printf("socket_error");
		return -1;
	}

	// �ּҸ� ���� �޴� ���� 
	SOCKADDR_IN ser_addr;
	ser_addr.sin_addr.s_addr = inet_addr("172.22.200.48");
	ser_addr.sin_port = htons(12345);
	ser_addr.sin_family = AF_INET;
	// �ּҸ� ���� �޴� ����


	int error = 0;
	error = bind(s, (struct sockaddr*)&ser_addr, sizeof(ser_addr)); // bind �Լ��� ���� �ü������ ����� �޴´�
	if (error == SOCKET_ERROR) {
		printf("bind error");
		return -1;
	}

	error = listen(s, SOMAXCONN); // ���� ����� ��Ʈ�� listen �Լ��� ���� listen ���·� ������ش�
	if (error == SOCKET_ERROR) {
		printf("listen_error");
		return -1;
	}

	SOCKET clt_s;
	SOCKADDR_IN clt_addr;
	int size = sizeof(clt_addr);
	clt_s = accept(s, (struct sockaddr*)&clt_addr, &size); // s ��� socket �ڵ鰪, ���濡�Լ� ��û�� ������ clt_addr�� ������ ����
	// clt_addr ���� client �� ������ ����ִ� ���̴�
	if (clt_s == INVALID_SOCKET) {
		printf("clt socket error");
		return -1;
	}

	int len;
	char buf[512];
	// len = recv(clt_s, buf, sizeof(buf), 0); // ���濡�Լ� �޼����� ������ �ϴ� �Լ�
	// �� ���������� client �� ip �� port ��ȣ�� �ʿ��ϱ� ������ �ʿ���� �Լ��� �ش��Ѵ�

	// clt_addr �� ��� ������ ������ �ִ�
	printf("client_port : %d\n", ntohs(clt_addr.sin_port)); // clt_addr ���� ��Ʈ ��ȣ�� ��Ʈ��ũ ������� ����Ǿ� �ֱ⿡ ȣ��Ʈ ������� ��ȯ�ؼ� ����Ѵ�
	// ntohs : network to host(short)
	printf("client_ip : %s\n", inet_ntoa(clt_addr.sin_addr)); // clt_addr ���� ip �� unsigned ���·� ����Ǿ� �ֱ� ������ ���ڿ��� �ٲپ� �ش�
	// inet_ntoa : network to ASCII
	closesocket(s);
	WSACleanup();
	return -1;
}