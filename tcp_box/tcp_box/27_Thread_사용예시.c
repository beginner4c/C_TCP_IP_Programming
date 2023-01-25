#include<stdio.h>
#include<windows.h>
#include<process.h>

unsigned __stdcall func1(void* arg) {
	int i;
	for (i = 0; i < 100; i++)
		printf("i : %d\n", i);
	return 0;
}
unsigned __stdcall func2(LPVOID arg) { // LPVOID 는 void*와 비슷하게 define된 값
	// L : long , P : pointer , VOID : void	자료형	==>> 4byte pointer void 형태, window에서 자주 사용한다
	int j;
	for (j = 0; j < 100; j++)
		printf("j : %d\n", j);
	return 0;
}

int main() {
	printf("main() 시작\n");

	printf("thread() 시작\n");

	unsigned long hthread1 = _beginthreadex(NULL, 0, func1, NULL, 0, NULL); // 함수가 성공한다면 식별 번호가 return된다
	// 상속 디스크립터, stack에 대한 size, 함수에 대한 주소, 인자값을 넘겨줄 값, 시작 설정 여부, ID 값
	// 함수 성공 시 handle 값이 return 된다고 생각하면 된다
	unsigned long hthread2 = _beginthreadex(NULL, 0, func2, NULL, 0, NULL);
	// _beginthreadex 함수가 성공하게 된다면 func1 과 func2 는 thread화 된다고 볼 수 있다
	
	/*
	while(1){
		printf("main()\n");
		Sleep(10000);
	}
	// 주석의 내용을 포함해서 실행해보고 비포함해서도 실행해보면
	// 차이가 있는것을 확인할 수 있다
	*/

	getch();

	return 0;
}