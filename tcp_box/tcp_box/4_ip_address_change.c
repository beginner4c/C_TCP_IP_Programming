#pragma comment(lib, "ws2_32")
#include<winsock2.h>
#include<stdio.h>

int main(int argc, char* argv[]) {
	char* ipv4 = "192.168.1.1"; // 문자열 192.168.1.1 입력
	printf("변환 전 : %s\n", ipv4); // 192.168.1.1 입력 확인
	printf("변환 후 : %d\n", inet_addr(ipv4)); // 위의 ip 주소 형태를 inet_addr 을 통해 16885952 로 변경

	IN_ADDR ipv4_su; // IN_ADDR 은 기본적으로 만들어진 구조체 자료형
	// ipv4_su 선언
	ipv4_su.s_addr = inet_addr(ipv4); // ipv4_su 내부에 s_addr 을 inet_addr 을 통해 16885952 를 192.168.1.1 로 저장
	printf("재 변환 : %s\n", inet_ntoa(ipv4_su)); // 변환된 ip 주소 확인
	return 0;
}