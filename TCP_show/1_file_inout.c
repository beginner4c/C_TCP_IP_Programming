#include<stdio.h>

main() {
	FILE* fp = fopen("C:\\Users\\user\\Desktop\\code_test\\TCP_IP_Socket\\IOtest.txt", "w");
	// fp �� �ּҸ� �ְ� ���� ���� ���ڴ�(���� ��� �ش� ��ġ�� ����� �ȴ�)
	fprintf(fp, "�̸� : ȫ�浿\n���� : 20\n�ּ� : ���¥��\n");
	// fp �� ����Ű�� ���Ͽ� " " ���� ������ �Է��ϰڴ�
	fclose(fp); // �ش� ������ �ݰڴ� 
	return 0;
}