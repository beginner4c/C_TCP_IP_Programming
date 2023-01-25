#include<stdio.h>
#include<windows.h>

int sum = 0;

DWORD WINAPI MyThread(LPVOID arg) {
	int num = (int)arg; // main�� num �� 100�� ���´�
	for (int i = 1; i <= num; i++)
		sum += i;
	return 0;
}

int main() {

	int num = 100;

	HANDLE hThread = CreateThread(NULL, 0, MyThread, (LPVOID)num, CREATE_SUSPENDED, NULL);
	// MyThread�� ������ȭ ���� num�� ���ڰ����� �ְ� ������ �Ͻ� ����
	// ��ӵ�ũ����, ���� ������, thread�� ���� �Լ�, �Լ��� ���� ���ڰ�, threadȭ �� �� ��� �ñ�, ID ��

	printf("������ ���� �� ��� ��� = %d\n", sum);
	ResumeThread(hThread);
	WaitForSingleObject(hThread, INFINITE);
	printf("������ ���� �� ��� ��� = %d\n", sum);

	CloseHandle(hThread);

	getch();

	return 0;
}