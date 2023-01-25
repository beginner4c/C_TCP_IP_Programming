#include<process.h>
#include<stdio.h>
#include<windows.h>

// 아래처럼 작성해야 공유자원에 대해서 Thread 간 충돌이 없다

int sum = 0;

CRITICAL_SECTION cs; // 임계영역 사용할 구조체 전역 변수

unsigned __stdcall func1(void* arg) { // Thread 함수 생성
	int i;
	EnterCriticalSection(&cs); // 공유자원 접근 시작

	for (i = 0; i < 100; i++) {
		sum += i;
		printf("sum : %d\n", sum);
	}

	LeaveCriticalSection(&cs); // 공유자원 접근 종료
	return 0;
}

int main() {
	InitializeCriticalSection(&cs); // 임게영역 생성
	
	for (int i = 0; i < 100; i++)
		_beginthreadex(NULL, 0, func1, NULL, 0, NULL);
	// 상속디스크립터, 스택 사이즈, thread로 만들 함수, 함수에 넣을 인자값, thread화 된 후 사용 시기, ID 값

	DeleteCriticalSection(&cs); // 임계영역 종료

	getch();

	return 0;
}