#include<process.h>
#include<stdio.h>
#include<windows.h>

// �Ʒ�ó�� �ۼ��ؾ� �����ڿ��� ���ؼ� Thread �� �浹�� ����

int sum = 0;

CRITICAL_SECTION cs; // �Ӱ迵�� ����� ����ü ���� ����

unsigned __stdcall func1(void* arg) { // Thread �Լ� ����
	int i;
	EnterCriticalSection(&cs); // �����ڿ� ���� ����

	for (i = 0; i < 100; i++) {
		sum += i;
		printf("sum : %d\n", sum);
	}

	LeaveCriticalSection(&cs); // �����ڿ� ���� ����
	return 0;
}

int main() {
	InitializeCriticalSection(&cs); // �ӰԿ��� ����
	
	for (int i = 0; i < 100; i++)
		_beginthreadex(NULL, 0, func1, NULL, 0, NULL);
	// ��ӵ�ũ����, ���� ������, thread�� ���� �Լ�, �Լ��� ���� ���ڰ�, threadȭ �� �� ��� �ñ�, ID ��

	DeleteCriticalSection(&cs); // �Ӱ迵�� ����

	getch();

	return 0;
}