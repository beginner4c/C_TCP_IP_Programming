#include<stdio.h>

main() {
	FILE* src = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\src.txt", "rt");
	// �ش� ��ġ�� ������ �б�� ����
	FILE* dst = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\dst.txt", "wt");
	// �ش� ��ġ�� ������ ����� ����
	char ch;

	if (src == NULL || dst == NULL) { // ���� �� �� �ϳ��� ������ �����Ǿ� ���� �ʴٸ�
		printf("No file\n"); // No file ���
	}

	while ((ch = fgetc(src)) != EOF) { // ch �� src �� ������ �����ͼ�
		fputc(ch, dst); // ch �� ������ dst �� �־��ش�
		// file �� ������ �����ͼ� �ֱ� ������ Enter �� ���� �� ������ �־ �Ȱ��� ����ȴ� 
	}
	fclose(src); fclose(dst); // ������ �ݴ´� 
}