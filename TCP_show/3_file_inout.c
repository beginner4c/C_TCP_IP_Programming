#include<stdio.h>

main() {
	FILE* fp;
	char ch;

	if ((fp = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\data.txt", "r")) == NULL)
		return 0;

	while ((ch = fgetc(fp)) != EOF) { // ch 에 fp 파일의 끝까지 내용을 가져온다
		putchar(ch); // space bar 를 기준으로 출력하게 된다
	}
}