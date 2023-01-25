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
	printf("이름 : ");
	gets(p->name); // p->name 위치에 입력
	printf("주소 : ");
	gets(p->address); // p->address 위치에 입력
	printf("나이 : ");
	scanf("%d", &p->age); // p-> age 에 입력
	return p;
}

main(int argc, char * argv[]) {
	ST* p; // 구조체 ST 형태의 p 선언
	p = func(); // p 에 func 함수를 넣어준다

	FILE* fp = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\test2.txt", "w");
	// 해당 위치의 파일을 쓰기 모드로 가져온다 

	fwrite(p->name, 1, strlen(p->name), fp);
	// fp 라는 위치에 p->name 의 내용을 적어주겠다
	fprintf(fp, "\n");
	fwrite(p->address, 1, strlen(p->address), fp);
	// fp 라는 위치에 p->address 의 내용을 적어주겠다
	fprintf(fp, "\n%d\n",p->age);
	
	fclose(fp);
	free(p);
}