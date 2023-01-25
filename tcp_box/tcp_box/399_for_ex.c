#include<windows.h>
#include<process.h>
#include<conio.h>
#include<stdio.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int x, y;

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

unsigned __stdcall func_1(void* arg) {
	int i;
	for (i = 0; i < 1000; i++) {
		gotoxy(x, y);
		printf("け");
		y++;
		Sleep(400);
		system("cls");
		gotoxy(x, y);
		printf("け");
	}
	return 0;
}

unsigned __stdcall func_2(LPVOID arg) {
	int j;
	char ch;
	for (j = 0; j < 1000; j++) {
		switch (getch()) {
		case LEFT:
			gotoxy(x--, y);
			printf("け");
			break;
		case RIGHT:
			gotoxy(x--, y);
			printf("け");
			break;
		case DOWN:
			gotoxy(x--, y);
			printf("け");
			break;
		}
		system("cls");
		gotoxy(x, y);
		printf("け");
	}
	return 0;
}

int main() {

	unsigned long hthread_1 = _beginthreadex(NULL, 0, func_1, NULL, 0, 0);
	unsigned long hthread_2 = _beginthreadex(0, 0, func_2, 0, 0, 0);
	Sleep(1000000);

	return 0;
}