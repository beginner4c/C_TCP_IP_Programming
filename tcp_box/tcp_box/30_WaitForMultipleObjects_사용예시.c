#include<stdio.h>
#include<windows.h>

DWORD WINAPI func1(LPVOID arg) { // 반환 자료형 DWORD 는 4byte 정수 표현에 사용한다
	// WINAPI 는 window 에서 사용하는 방식이다
	int i;
	for (i = 0; i < 20; i++) {
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

	HANDLE hThread[2];

	hThread[0] = CreateThread(NULL, 0, func1, NULL, 0, NULL); // 함수의 return 되는 값은 handle 값
	// 상속디스크립터, 스택 사이즈, thread로 만들 함수, 함수에 넣을 인자값, thread화 된 후 사용 시기, ID 값
	hThread[1] = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	getch();

	return 0;
}