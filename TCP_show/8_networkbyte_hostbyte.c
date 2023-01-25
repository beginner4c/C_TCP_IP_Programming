#pragma comment(lib, "ws2_32")
#include<winsock2.h>
#include<stdio.h>

int main(int argc, char* argv[]) {
	short x1 = 0x1234, x2;
	int y1 = 0x12345678, y2;
	
	x2 = htons(x1);
	y2 = htonl(y1);
	
	printf("\n[네트워크 바이트 -> 호스트 바이트]\n");
	printf("0x%x -> 0x%x\n", x2, ntohs(x2));
	printf("0x%x -> 0x%x\n", y2, ntohl(y2));
}