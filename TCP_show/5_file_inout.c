#include<stdio.h>
#define BUF_SIZE 1024

main() {
	// fread(buffer, sizeof(char), 12, fp);
	// => buffer ��� ��ġ�� fp �� ������ 1 byte �� 12 �� �ݺ��ؼ� �������ڴ�
	// fwrite(buffer, sizeof(char), 12, fp);
	// => fp ��� ��ġ�� buffer �� ������ 1 byte �� 12 �� �ݺ��ؼ� �־��ְڴ�

	FILE* src = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\src.txt", "rb");
	FILE* dst = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\dst.txt", "wb");
	char str[BUF_SIZE];

	if (src == NULL || dst == NULL)
		printf("File No Open\n");

	fseek(src, 0, SEEK_END); // src ������ Ŀ�� ��ġ�� 0 ������ ������ �̵����Ѷ�

	int size = ftell(src); // ���Ͽ� ���� ��ü ũ�Ⱑ byte ������ size �� ������ �ȴ�

	// fseek(src,0,SEEK_SET);
	// src �� Ŀ�� ��ġ�� ������ ���� ó������ �̵���Ű�ڴ�

	fread(str, 1, size, src);
	// str �� ������ 1 byte �� size ũ�� ��ŭ src ���� �������ڴ�
	// ���⼭ ������ fseek �� ���� src ���� Ŀ���� ��ġ�� ������ �Ű�� ������ ������ ���� �������� �ȴ�
	fwrite(str, 1, size, dst);
	// dst ��ġ�� str �� ������ 1 byte �� size ũ�� ��ŭ �־��ְڴ�

	fclose(src); fclose(dst);
}