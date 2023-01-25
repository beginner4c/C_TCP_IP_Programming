#include<stdio.h>
#define BUF_SIZE 1024

main() {
	// fread(buffer, sizeof(char), 12, fp);
	// => buffer 라는 위치에 fp 의 내용을 1 byte 씩 12 번 반복해서 가져오겠다
	// fwrite(buffer, sizeof(char), 12, fp);
	// => fp 라는 위치에 buffer 의 내용을 1 byte 씩 12 번 반복해서 넣어주겠다

	FILE* src = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\src.txt", "rb");
	FILE* dst = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\dst.txt", "wb");
	char str[BUF_SIZE];

	if (src == NULL || dst == NULL)
		printf("File No Open\n");

	fseek(src, 0, SEEK_END); // src 파일의 커서 위치를 0 번에서 끝으로 이동시켜라

	int size = ftell(src); // 파일에 대한 전체 크기가 byte 단위로 size 에 저장이 된다

	// fseek(src,0,SEEK_SET);
	// src 의 커서 위치를 파일의 제일 처음으로 이동시키겠다

	fread(str, 1, size, src);
	// str 의 공간에 1 byte 씩 size 크기 만큼 src 에서 가져오겠다
	// 여기서 문제는 fseek 를 통해 src 파일 커서의 위치를 끝으로 옮겼기 때문에 쓰레기 값만 가져오게 된다
	fwrite(str, 1, size, dst);
	// dst 위치에 str 의 내용을 1 byte 씩 size 크기 만큼 넣어주겠다

	fclose(src); fclose(dst);
}