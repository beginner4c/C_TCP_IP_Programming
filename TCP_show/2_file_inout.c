#include<stdio.h>

main(int argc, char ** argv) {
	FILE* fp;
	int i, no = 0, sum = 0;
	if ((fp = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\data.txt", "r")) == NULL) {
		// fp 가 가르키는 위치를 읽어오는데 해당 위치에 파일이 없을 경우 NULL 값이 반환된다
		// NULL 값이 반환 될 경우
		printf("File open error\n"); // 에러 메시지 출력
	}
	while (fscanf(fp, "%d", &i) != EOF) {
		// 파일의 내용이 끝이 아닐 경우 space bar 를 기준으로 정수를 가져와 i 에 정수형으로 저장
		sum += i; // 가져온 i 를 정수 sum 에 더해서 저장
			++no; // 반복 횟수 확인
	}
	if (no == 0) // 만약 해당 파일 안에 아무런 내용이 없을 경우
		printf("No data\n"); // 출력
	else { // 해당 파일 안에 내용이 하나라도 있었을 경우
		printf("Total %d number\n", no); // 몇 번 반복했는지
		printf("Sum = %d\n", sum); // 안에 들어있던 정수들의 합은 얼마였는지
		printf("Average = %.2f\n", (float)sum/(float)no); // 정수들의 평균은 얼마였는지 확인한다
		fclose(fp); // 끝으로 파일을 닫는다
	}
}