#include<windows.h>
#include<stdio.h>

int sum = 0;

DWORD WINAPI MyThread(LPVOID arg) {
	int num = (int)arg; // 100 �� ������ �ȴ�
	for (int i = 1; i <= num; i++)
		sum += i;
	return 0;
}

int main() {
	int num = 100;

	HANDLE hThread = CreateThread(NULL, 0, MyThread, (LPVOID)num, CREATE_SUSPENDED, NULL); // ���ڰ��� �ڷ����� �����ش�
	// ��ӵ�ũ����, ���� ������, thread�� ���� �Լ�, �Լ��� ���� ���ڰ�, threadȭ �� �� ��� �ñ�, ID ��

	printf("������ ���� �� ��� ��� = %d\n", sum);
	ResumeThread(hThread); // hThread ������ �����
	WaitForSingleObject(hThread, INFINITE); // hThread �����尡 ���� ������ ���
	printf("������ ���� �� ��� ��� = %d\n", sum);

	CloseHandle(hThread); // hThread handle �� ����

	getch();

	return 0;
}