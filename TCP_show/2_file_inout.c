#include<stdio.h>

main(int argc, char ** argv) {
	FILE* fp;
	int i, no = 0, sum = 0;
	if ((fp = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\data.txt", "r")) == NULL) {
		// fp �� ����Ű�� ��ġ�� �о���µ� �ش� ��ġ�� ������ ���� ��� NULL ���� ��ȯ�ȴ�
		// NULL ���� ��ȯ �� ���
		printf("File open error\n"); // ���� �޽��� ���
	}
	while (fscanf(fp, "%d", &i) != EOF) {
		// ������ ������ ���� �ƴ� ��� space bar �� �������� ������ ������ i �� ���������� ����
		sum += i; // ������ i �� ���� sum �� ���ؼ� ����
			++no; // �ݺ� Ƚ�� Ȯ��
	}
	if (no == 0) // ���� �ش� ���� �ȿ� �ƹ��� ������ ���� ���
		printf("No data\n"); // ���
	else { // �ش� ���� �ȿ� ������ �ϳ��� �־��� ���
		printf("Total %d number\n", no); // �� �� �ݺ��ߴ���
		printf("Sum = %d\n", sum); // �ȿ� ����ִ� �������� ���� �󸶿�����
		printf("Average = %.2f\n", (float)sum/(float)no); // �������� ����� �󸶿����� Ȯ���Ѵ�
		fclose(fp); // ������ ������ �ݴ´�
	}
}