#include<stdio.h>
#include<windows.h>

DWORD WINAPI func1(LPVOID arg) { // ��ȯ �ڷ��� DWORD �� 4byte ���� ǥ���� ����Ѵ�
	// WINAPI �� window ���� ����ϴ� ����̴�
	int i;
	for (i = 0; i < 100; i++) {
		printf("i : %d\n", i);
	}
	return 0;
}

DWORD WINAPI func2(LPVOID arg) {
	int j;
	for (j = 0; j < 100; j++) {
		printf("j : %d\n", j);
	}
	return 0;
}

int main() {
	HANDLE hThread1 = CreateThread(NULL, 0, func1, NULL, 0, NULL); // �Լ��� return �Ǵ� ���� handle ��
	// ��ӵ�ũ����, ���� ������, thread�� ���� �Լ�, �Լ��� ���� ���ڰ�, threadȭ �� �� ��� �ñ�, ID ��
	HANDLE hThread2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	while (1) {
		printf("main()\n");
		Sleep(3000);
	}

	getch();

	return 0;
}