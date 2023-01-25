#include<stdio.h>

main() {
	FILE* fp = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\IOtest.txt", "w");
	// fp 에 주소를 넣고 쓰기 모드로 열겠다(없을 경우 해당 위치에 만들게 된다)
	fprintf(fp, "이름 : 홍길동\n나이 : 20\n주소 : 산골짜기\n");
	// fp 가 가르키는 파일에 " " 안의 내용을 입력하겠다
	fclose(fp); // 해당 파일을 닫겠다 
	return 0;
}