#include<stdio.h>
#include<windows.h>

DWORD WINAPI func1(LPVOID arg) {
	int i;
	for (i = 0; i < 10; i++)
		printf("i : %d\n", i);
	return 0;
}

DWORD WINAPI func2(LPVOID arg) {
	int j;
	for (j = 0; j < 10; j++)
		printf("j : %d\n", j);
	return 0;
}

int main() {

	HANDLE hThread1, hThread2;

	hThread1 = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	// ��ӵ�ũ����, ���� ������, thread�� ���� �Լ�, �Լ��� ���� ���ڰ�, threadȭ �� �� ��� �ñ�, ID ��
	hThread2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	printf("func1 �Ͻ�����\n");
	SuspendThread(hThread1); // hThread1 ������ �Ͻ�����
	WaitForSingleObject(hThread2, INFINITE); // hThread2 �����尡 ���������� ������ ���

	printf("fucn1 �����\n");
	ResumeThread(hThread1); // �Ͻ��������� hThread1 ������ �����
	WaitForSingleObject(hThread1, INFINITE); // hThread1 �����尡 ���������� ������ ���

	getch();

	return 0;
}