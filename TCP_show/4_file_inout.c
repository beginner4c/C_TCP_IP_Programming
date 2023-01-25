#include<stdio.h>

main() {
	FILE* src = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\src.txt", "rt");
	// 해당 위치의 파일을 읽기로 개방
	FILE* dst = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\dst.txt", "wt");
	// 해당 위치의 파일을 쓰기로 개방
	char ch;

	if (src == NULL || dst == NULL) { // 만약 둘 중 하나라도 파일이 생성되어 있지 않다면
		printf("No file\n"); // No file 출력
	}

	while ((ch = fgetc(src)) != EOF) { // ch 는 src 의 내용을 가져와서
		fputc(ch, dst); // ch 의 내용을 dst 에 넣어준다
		// file 의 끝까지 가져와서 넣기 때문에 Enter 를 통해 줄 변경이 있어도 똑같이 복사된다 
	}
	fclose(src); fclose(dst); // 파일을 닫는다 
}