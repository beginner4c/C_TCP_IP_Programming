#include<stdio.h>
#include<windows.h>
#include<process.h>

// �Ʒ�ó�� �ۼ����� �� Thread ���� ����ȭ�� ���� �����ڿ��� ������������ ������ ���
// �ٸ� Thread�� ����� ���� �״�� ������ ���ɼ��� �ִ�

int sum = 0; // ���� �ڿ�

unsigned __stdcall func1(void* arg) { // Thread �Լ� ����
	int i;
	for (i = 0; i < 100; i++) {
		sum += i;
		printf("sum : %d\n", sum);
	}
	return 0;
}

int main() {
	for (int i = 0; i < 100; i++)
		_beginthreadex(NULL, 0, func1, NULL, 0, NULL);
	// ��ӵ�ũ����, ���� ������, thread�� ���� �Լ�, �Լ��� ���� ���ڰ�, threadȭ �� �� ��� �ñ�, ID ��

	getch();

	return 0;
}