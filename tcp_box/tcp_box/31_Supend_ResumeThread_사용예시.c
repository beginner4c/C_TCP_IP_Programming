#include<stdio.h>
#include<windows.h>

DWORD WINAPI func1(LPVOID arg) { // 반환 자료형 DWORD 는 4byte 정수 표현에 사용한다
	// WINAPI 는 window 에서 사용하는 방식이다
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
	HANDLE hThread1, hThread2;

	hThread1 = CreateThread(NULL, 0, func1, NULL, 0, NULL);
	// 상속디스크립터, 스택 사이즈, thread로 만들 함수, 함수에 넣을 인자값, thread화 된 후 사용 시기, ID 값
	hThread2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);

	printf("func1 일시중지\n");
	SuspendThread(hThread1); // hThread1 스레드 일시 중지
	WaitForSingleObject(hThread2, INFINITE); // hThread2 스레드가 끝날 때까지 대기

	printf("func1 재시작\n");
	ResumeThread(hThread1); // hThread1 스레드 재시작
	WaitForSingleObject(hThread1, INFINITE); // hThread1 스레드가 끝날 때까지 대기

	getch();

	return 0;
}