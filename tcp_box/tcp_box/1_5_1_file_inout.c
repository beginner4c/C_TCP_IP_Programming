#include<stdio.h>

main() {
	// 5_file_inout 의 내용을 동적할당으로 고칠 때 사용
	/*
	fseek(src,0,SEEK_END);
	int size = ftell(src);
	fseek(src,0,SEEK_SET);

	char *pc;

	pc = (char*)malloc(size);
	fread(pc,1,size,src);
	fwrite(pc,1,size,dst);
	free(pc);
	fclose(src);
	fclose(dst);
	*/
}