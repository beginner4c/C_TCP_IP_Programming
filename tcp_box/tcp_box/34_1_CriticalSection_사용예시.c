#include<process.h>
#include<windows.h>
#include<stdio.h>

// Thread ����ȭ�� ���� ���� �ڿ��� �� �� �̻��� Thread�� ������ ��
// �ϳ��� Thread�� �����ϰ� �������� ����ϰ� �����

int A[100];
CRITICAL_SECTION cs; // �Ӱ迵�� ����� ����ü ��������
// Enter,LeaveCriticalSection Function ����� ���� ����

unsigned __stdcall func1(void* arg) { // Thread Function ����
	EnterCriticalSection(&cs); // �����ڿ� ���� ����
	// �����ڿ��� �����߱� ������ �ٸ� �Լ��� �����ڿ��� ������ �� ����

	printf("func1\n");
	for (int i = 0; i < 100; i++) { // 3�� 100�� ���
		A[i] = 3;
		printf(" %d", A[i]);
		Sleep(10);
	}
	LeaveCriticalSection(&cs); // �����ڿ� ���� ����
	// ���� ���ĺ��� �ٸ� �Լ��� �����ڿ��� ������ �� �ְ� �ȴ�
	
	return 0;
}

unsigned __stdcall func2(void* arg) {
	EnterCriticalSection(&cs); // �����ڿ� ���� ����
	// �����ڿ��� �����߱� ������ �ٸ� �Լ��� �����ڿ��� ������ �� ����

	printf("\nfunc2\n");
	for (int j = 99; j >= 0; j--) { // 4�� 100 �� ���
		A[j] = 4;
		printf(" %d", A[j]);
		Sleep(10);
	}

	LeaveCriticalSection(&cs); // �����ڿ� ���� ����
	// ���� ���ĺ��� �ٸ� �Լ��� �����ڿ��� ������ �� �ְ� �ȴ�

	return 0;
}

int main() {
	InitializeCriticalSection(&cs); // �Ӱ迵�� ����

	printf("main() start\n");

	HANDLE hThread1, hThread2; // Thread �Լ� �ڵ鰪�� �޾��� ����
	hThread1 = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, NULL); // func1�� ������ ȭ
	// ��ӵ�ũ����, ���� ������, thread�� ���� �Լ�, �Լ��� ���� ���ڰ�, threadȭ �� �� ��� �ñ�, ID ��
	hThread2 = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, NULL); // func2�� ������ ȭ

	WaitForSingleObject(hThread1, INFINITE); // hThread1 ���� ������ ������ Thread�� ���
	WaitForSingleObject(hThread2, INFINITE); // hThread2 ���� ������ ������ Thread�� ���

	DeleteCriticalSection(&cs); // �Ӱ迵�� ����
	printf("\n");

	getch();

	return 0;
}