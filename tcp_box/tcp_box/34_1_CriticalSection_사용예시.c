#include<process.h>
#include<windows.h>
#include<stdio.h>

// Thread 동기화로 인해 공유 자원에 두 개 이상의 Thread가 몰렸을 때
// 하나의 Thread만 접근하고 나머지는 대기하게 만든다

int A[100];
CRITICAL_SECTION cs; // 임계영역 사용할 구조체 전역변수
// Enter,LeaveCriticalSection Function 사용할 전역 변수

unsigned __stdcall func1(void* arg) { // Thread Function 생성
	EnterCriticalSection(&cs); // 공유자원 접근 시작
	// 공유자원에 접근했기 때문에 다른 함수는 공유자원에 접근할 수 없다

	printf("func1\n");
	for (int i = 0; i < 100; i++) { // 3을 100번 출력
		A[i] = 3;
		printf(" %d", A[i]);
		Sleep(10);
	}
	LeaveCriticalSection(&cs); // 공유자원 접근 종료
	// 종료 이후부터 다른 함수가 공유자원에 접근할 수 있게 된다
	
	return 0;
}

unsigned __stdcall func2(void* arg) {
	EnterCriticalSection(&cs); // 공유자원 접근 시작
	// 공유자원에 접근했기 때문에 다른 함수는 공유자원에 접근할 수 없다

	printf("\nfunc2\n");
	for (int j = 99; j >= 0; j--) { // 4를 100 번 출력
		A[j] = 4;
		printf(" %d", A[j]);
		Sleep(10);
	}

	LeaveCriticalSection(&cs); // 공유자원 접근 종료
	// 종료 이후부터 다른 함수가 공유자원에 접근할 수 있게 된다

	return 0;
}

int main() {
	InitializeCriticalSection(&cs); // 임계영역 생성

	printf("main() start\n");

	HANDLE hThread1, hThread2; // Thread 함수 핸들값을 받아줄 변수
	hThread1 = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, NULL); // func1를 스레드 화
	// 상속디스크립터, 스택 사이즈, thread로 만들 함수, 함수에 넣을 인자값, thread화 된 후 사용 시기, ID 값
	hThread2 = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, NULL); // func2를 스레드 화

	WaitForSingleObject(hThread1, INFINITE); // hThread1 종료 전까지 나머지 Thread는 대기
	WaitForSingleObject(hThread2, INFINITE); // hThread2 종료 전까지 나머지 Thread는 대기

	DeleteCriticalSection(&cs); // 임계영역 종료
	printf("\n");

	getch();

	return 0;
}