#pragma comment(lib, "ws2_32")
#include<winsock2.h>
#include<stdio.h>

int main(int argc, char* argv[]) {
	char* ipv4 = "192.168.1.1"; // ���ڿ� 192.168.1.1 �Է�
	printf("��ȯ �� : %s\n", ipv4); // 192.168.1.1 �Է� Ȯ��
	printf("��ȯ �� : %d\n", inet_addr(ipv4)); // ���� ip �ּ� ���¸� inet_addr �� ���� 16885952 �� ����

	IN_ADDR ipv4_su; // IN_ADDR �� �⺻������ ������� ����ü �ڷ���
	// ipv4_su ����
	ipv4_su.s_addr = inet_addr(ipv4); // ipv4_su ���ο� s_addr �� inet_addr �� ���� 16885952 �� 192.168.1.1 �� ����
	printf("�� ��ȯ : %s\n", inet_ntoa(ipv4_su)); // ��ȯ�� ip �ּ� Ȯ��
	return 0;
}