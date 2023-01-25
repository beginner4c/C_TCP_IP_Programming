#include<windows.h>
#include<stdio.h>

int sum = 0;

DWORD WINAPI MyThread(LPVOID arg) {
	int num = (int)arg; // 100 이 들어오게 된다
	for (int i = 1; i <= num; i++)
		sum += i;
	return 0;
}

int main() {
	int num = 100;

	HANDLE hThread = CreateThread(NULL, 0, MyThread, (LPVOID)num, CREATE_SUSPENDED, NULL); // 인자값은 자료형을 맞춰준다
	// 상속디스크립터, 스택 사이즈, thread로 만들 함수, 함수에 넣을 인자값, thread화 된 후 사용 시기, ID 값

	printf("스레드 실행 전 계산 결과 = %d\n", sum);
	ResumeThread(hThread); // hThread 스레드 재실행
	WaitForSingleObject(hThread, INFINITE); // hThread 스레드가 끝날 때까지 대기
	printf("스레드 실행 후 계산 결과 = %d\n", sum);

	CloseHandle(hThread); // hThread handle 값 종료

	getch();

	return 0;
}