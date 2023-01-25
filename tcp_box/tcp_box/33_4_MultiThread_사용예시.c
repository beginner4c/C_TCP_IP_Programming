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
	for (j = 0; j < 50; j++)
		printf("j : %d\n", j);
	return 0;
}

int main() {

	HANDLE hThread[2];

	hThread[0] = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	// 상속디스크립터, 스택 사이즈, thread로 만들 함수, 함수에 넣을 인자값, thread화 된 후 사용 시기, ID 값
	hThread[1] = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE); // hThread의 2개 스레드가 끝날 때 까지 나머지는 대기
	// 스레드 갯수, 스레드 배열, 둘 다 종료 시 나머지 시작, 기다릴 시간
	// TRUE = 1, FALSE = 0

	CloseHandle(hThread); // Thread Handle 종료

	getch();

	return 0;
}