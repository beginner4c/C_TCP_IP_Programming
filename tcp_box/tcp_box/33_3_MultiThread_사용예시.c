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
	// 상속디스크립터, 스택 사이즈, thread로 만들 함수, 함수에 넣을 인자값, thread화 된 후 사용 시기, ID 값
	HANDLE hThread2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	WaitForSingleObject(hThread1, INFINITE); // hThread1 스레드가 끝날 때까지 나머지는 대기
	WaitForSingleObject(hThread2, INFINITE); // hThread2 스레드가 끝날 때까지 나머지는 대기

	CloseHandle(hThread1); // Thread Handle 종료
	CloseHandle(hThread2);

	getch();

	return 0;
}