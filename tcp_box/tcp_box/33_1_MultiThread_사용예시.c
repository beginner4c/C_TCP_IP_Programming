#include<stdio.h>
#include<windows.h>
#include<process.h>

unsigned __stdcall func1(void* arg) {
	int i;
	for (i = 0; i < 100; i++)
		printf("i : %d\n", i);
	return 0;
}

unsigned __stdcall func2(LPVOID arg) {
	int j;
	for (j = 0; j < 100; j++)
		printf("j : %d\n", j);
	return 0;
}

int main() {
	printf("main() 시작\n");

	printf("Thread() 시작\n");

	unsigned long hThread1 = _beginthreadex(NULL, 0, func1, NULL, 0, NULL);
	// 상속디스크립터, 스택 사이즈, thread로 만들 함수, 함수에 넣을 인자값, thread화 된 후 사용 시기, ID 값
	unsigned long hThread2 = _beginthreadex(NULL, 0, func2, NULL, 0, NULL);

	/*
	while(1){
		printf("main()\n");
		Sleep(10000);
	}
	// 주석이 있고 없고의 차이를 확인해보자
	*/

	return 0;
}