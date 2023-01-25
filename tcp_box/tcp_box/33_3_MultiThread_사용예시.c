#include<stdio.h>
#include <windows.h>

DWORD WINAPI func1(LPVOID arg) {
	int i;
	for (i = 0; i < 20; i++)
		printf("i : %d\n", i);
	return 0;
}

DWORD WINAPI func2(LPVOID arg) {
	int j;
	for (j = 0; j < 20; j++)
		printf("j : %d\n", j);
	return 0;
}

int main() {

	HANDLE hThread1 = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	// ��ӵ�ũ����, ���� ������, thread�� ���� �Լ�, �Լ��� ���� ���ڰ�, threadȭ �� �� ��� �ñ�, ID ��
	HANDLE hThread2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	WaitForSingleObject(hThread1, INFINITE); // hThread1 �����尡 ���� ������ �������� ���
	WaitForSingleObject(hThread2, INFINITE); // hThread2 �����尡 ���� ������ �������� ���

	CloseHandle(hThread1); // Thread Handle ����
	CloseHandle(hThread2);

	getch();

	return 0;
}