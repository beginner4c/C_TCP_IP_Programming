#include<stdio.h>
#include<windows.h>
#include<process.h>

// 아래처럼 작성했을 때 Thread 간의 동기화가 없어 공유자원에 무제한적으로 접근할 경우
// 다른 Thread가 사용한 값을 그대로 가져갈 가능성도 있다

int sum = 0; // 공유 자원

unsigned __stdcall func1(void* arg) { // Thread 함수 생성
	int i;
	for (i = 0; i < 100; i++) {
		sum += i;
		printf("sum : %d\n", sum);
	}
	return 0;
}

int main() {
	for (int i = 0; i < 100; i++)
		_beginthreadex(NULL, 0, func1, NULL, 0, NULL);
	// 상속디스크립터, 스택 사이즈, thread로 만들 함수, 함수에 넣을 인자값, thread화 된 후 사용 시기, ID 값

	getch();

	return 0;
}