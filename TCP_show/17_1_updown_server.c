// ��ó���� ����
// server
#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int ran, cnt; // random �� count ���� ����
// ���� ������ �̸� �ʱ�ȭ �Ǿ� 0 �̴�

// ����� �Լ� ����
int up(int user) { // 
	int result;
	printf("updown game start\n");
	if (!ran) // ran �� 0 �� ���
		ran = rand_(); // ran �� rand_ �Լ� ȣ�� (������ ���� ������ ����)
	result = check(user); // 
	return result;
}

int rand_() { // ������ �ϳ��� ���� �����ִ� �Լ�
	srand(time(NULL));
	return rand() % 99 + 1;
}

int check(int user) { // ���� ���� random �� ���� �񱳸� ���� �Լ�
	printf("input : %d\n", user);
	printf("com : %d\n", ran);
	if (user > ran) { // ���� ���� random �� �� ���� Ŭ ��
		cnt++;
		return 1;
	}
	else if (user < ran) { // ���� ���� random �� �� ���� ���� ��
		cnt++;
		return -1;
	}
	else { // ���� ���� random �� ���� ���� ��
		cnt++;
		return 0;
	}
	system("pause");
	system("cls");
}

typedef struct u {
	int num;
	char str[1024];
}ST; // Ŭ���̾�Ʈ�� ������ ����ü ����

main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // winsock dll �ε�

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0); // ���� ����
	if (s == INVALID_SOCKET) { // ���� �߻� Ȯ��
		printf("socket error\n");
		return -1;
	}

	SOCKADDR_IN addr; // IPv4 �� �ּ� ����ü ����
	addr.sin_family = AF_INET; // IPv4 �� ��
	addr.sin_port = htons(12345); // port ��ȣ ����
	addr.sin_addr.S_un.S_addr = inet_addr("172.22.200.48"); // server ip ����
	// addr.sin_addr.s_addr = ���� ip ���� �� ��� ����

	int error; // error Ȯ�� �� ���� ����
	error = bind(s, (SOCKADDR*)&addr, sizeof(addr)); // �ü������ ����� �޾��ִ� ����
	if (error == SOCKET_ERROR) {
		printf("bind error\n");
		return -1;
	}

	error = listen(s, SOMAXCONN); // ��Ʈ�� listening ���·� ����(���)
	if (error == SOCKET_ERROR) { // ��Ʈ listen �Լ� ���� �� 
		printf("listen error\n");
		return -1;
	}

	SOCKET CLT_s; // ������ �� ����� SOCKET ����
	SOCKADDR_IN CLT_addr; // IPv4 �� ����ü ����
	int size = sizeof(CLT_addr); // IPv4 �� ����ü�� ũ�� ����

	CLT_s = accept(s, (SOCKADDR*)&CLT_addr, &size); // ���� ���
	if (CLT_s == INVALID_SOCKET) { // ���� ��� �Լ� ���� ��
		printf("accept error\n");
		return -1;
	}

	char buf[1024];
	int len;
	int user;
	int result;
	ST st;

	while (1) {
		len = recv(CLT_s, (char*)&user, sizeof(user), 0); // client ���� ���� ������ len �� ����
		// recv �Լ��� ������ ��� user���� client ���� ���� ���ڰ� ��� �ִ�
		if (len == SOCKET_ERROR) { // recv �Լ� ���� ��
			printf("recv error\n");
			return -1;
		}
		result = up(user); // result �� up �Լ��� ���� 1 or -1 or 0 �� �޾ƿ� ��
		if (result == 1) { // ������ �����Ͱ� random �� ���� ���� ���
			printf("==== UP ====\n");
			sprintf(st.str, "==== UP ====\n"); // st.str �� ���ڿ��� ����
			send(CLT_s, (char)&st, sizeof(st), 0); // st ����ü�� �����͸� send �Լ��� ���� ����
		}
		else if (result == -1) { // ������ �����Ͱ� random �� ���� Ŭ ���
			printf("==== DOWN ====\n");
			sprintf(st.str, "==== DOWN ====\n"); // st.str �� ���ڿ��� ����
			send(CLT_s, (char*)&st, sizeof(st), 0); // st ����ü�� �����͸� send �Լ��� ���� ����
		}
		else { // ������ �����Ϳ� random ���� ���� ���
			printf("%d �� ���� ����\n", cnt);
			sprintf(st.str, "%d �� ���� ����\n\n == !! Clear !! ==\n", cnt); // st.str �� ���ڿ��� ����
			st.num = 1; // st.num �� 1 ���� (������ ����ٴ� ���� �˷��ֱ� ���� ��)
			send(CLT_s, (char)&st, sizeof(st), 0); // st ����ü�� �����͸� send �Լ��� ���� ����
			break; // while �� Ż��
		}
	}

	// ����ߴ� ���ϵ� ����
	closesocket(CLT_s);
	closesocket(s);
	WSACleanup(); // dll ��ε�
	
	return 0;
}