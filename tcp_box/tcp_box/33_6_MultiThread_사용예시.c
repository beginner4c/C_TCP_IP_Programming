#include<stdio.h>
#include<windows.h>

int sum = 0;

DWORD WINAPI MyThread(LPVOID arg) {
	int num = (int)arg; // main의 num 값 100이 들어온다
	for (int i = 1; i <= num; i++)
		sum += i;
	return 0;
}

int main() {

	int num = 100;

	HANDLE hThread = CreateThread(NULL, 0, MyThread, (LPVOID)num, CREATE_SUSPENDED, NULL);
	// MyThread를 스레드화 시켜 num을 인자값으로 넣고 스레드 일시 정지
	// 상속디스크립터, 스택 사이즈, thread로 만들 함수, 함수에 넣을 인자값, thread화 된 후 사용 시기, ID 값

	printf("스레드 실행 전 계산 결과 = %d\n", sum);
	ResumeThread(hThread);
	WaitForSingleObject(hThread, INFINITE);
	printf("스레드 실행 후 계산 결과 = %d\n", sum);

	CloseHandle(hThread);

	getch();

	return 0;
}