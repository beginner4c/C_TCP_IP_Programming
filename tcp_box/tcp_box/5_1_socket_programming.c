#pragma comment(lib, "ws2_32")
#include<winsock2.h>
#include<stdio.h>

int main() {
	WSADATA wsa; // WSADATA �� ����ü�� �ڷ���
	// WSADATA ����ü wsa ����
	WSAStartup(MAKEWORD(2, 2), &wsa); // ���ʷ� dll �ʱ�ȭ �۾�
	// MAKEWORD ��� define �� ������ �츮�� ����� ������ �Ѱ��ش�
	// wsa ��� ������ ���� �˾Ƽ� �������ְ� �ȴ�

	printf("winsock start");

	WSACleanup(); // dll load �۾��� �ٽ� unload �����ش�

	return 0;
}