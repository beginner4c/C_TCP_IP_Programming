#include<stdio.h>
#include<windows.h>
#include<process.h>

unsigned __stdcall func1(void* arg) {
	int i;
	for (i = 0; i < 100; i++)
		printf("i : %d\n", i);
	return 0;
}
unsigned __stdcall func2(LPVOID arg) { // LPVOID �� void*�� ����ϰ� define�� ��
	// L : long , P : pointer , VOID : void	�ڷ���	==>> 4byte pointer void ����, window���� ���� ����Ѵ�
	int j;
	for (j = 0; j < 100; j++)
		printf("j : %d\n", j);
	return 0;
}

int main() {
	printf("main() ����\n");

	printf("thread() ����\n");

	unsigned long hthread1 = _beginthreadex(NULL, 0, func1, NULL, 0, NULL); // �Լ��� �����Ѵٸ� �ĺ� ��ȣ�� return�ȴ�
	// ��� ��ũ����, stack�� ���� size, �Լ��� ���� �ּ�, ���ڰ��� �Ѱ��� ��, ���� ���� ����, ID ��
	// �Լ� ���� �� handle ���� return �ȴٰ� �����ϸ� �ȴ�
	unsigned long hthread2 = _beginthreadex(NULL, 0, func2, NULL, 0, NULL);
	// _beginthreadex �Լ��� �����ϰ� �ȴٸ� func1 �� func2 �� threadȭ �ȴٰ� �� �� �ִ�
	
	/*
	while(1){
		printf("main()\n");
		Sleep(10000);
	}
	// �ּ��� ������ �����ؼ� �����غ��� �������ؼ��� �����غ���
	// ���̰� �ִ°��� Ȯ���� �� �ִ�
	*/

	getch();

	return 0;
}