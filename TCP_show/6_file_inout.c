#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct st {
	char name[20];
	char address[50];
	int age;
}ST;

ST* func() {
	ST* p = (ST*)malloc(sizeof(ST));
	printf("�̸� : ");
	gets(p->name); // p->name ��ġ�� �Է�
	printf("�ּ� : ");
	gets(p->address); // p->address ��ġ�� �Է�
	printf("���� : ");
	scanf("%d", &p->age); // p-> age �� �Է�
	return p;
}

main(int argc, char * argv[]) {
	ST* p; // ����ü ST ������ p ����
	p = func(); // p �� func �Լ��� �־��ش�

	FILE* fp = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\test2.txt", "w");
	// �ش� ��ġ�� ������ ���� ���� �����´� 

	fwrite(p->name, 1, strlen(p->name), fp);
	// fp ��� ��ġ�� p->name �� ������ �����ְڴ�
	fprintf(fp, "\n");
	fwrite(p->address, 1, strlen(p->address), fp);
	// fp ��� ��ġ�� p->address �� ������ �����ְڴ�
	fprintf(fp, "\n%d\n",p->age);
	
	fclose(fp);
	free(p);
}