#include<stdio.h>

main() {
	FILE* fp;
	char ch;

	if ((fp = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\data.txt", "r")) == NULL)
		return 0;

	while ((ch = fgetc(fp)) != EOF) { // ch �� fp ������ ������ ������ �����´�
		putchar(ch); // space bar �� �������� ����ϰ� �ȴ�
	}
}