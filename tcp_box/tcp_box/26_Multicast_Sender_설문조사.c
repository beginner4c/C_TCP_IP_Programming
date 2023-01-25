// IPPROTO_IP를 이용해 설문조사 프로그램 작성
// sender와 receiver 따로 존재
// sender는 설문 내용의 문자열을 receiver들에게 전송
// receiver는 전송 내용을 화면에 출력 후 입력 값을 sender에게 유니캐스트 전송
// sender는 receiver들의 입력 값을 다시 출력


#include<winsock2.h>
#include<stdio.h>
#include<ws2tcpip.h> // 옵션 설정 시 필요 헤더
#pragma comment(lib, "ws2_32.lib")

// MULTICAST 통신 => 일 대 다수의 통신 방법

typedef struct msg {
	int a_num;
	char q_str[512];
}_msg;

int main() {
	WSADATA wsa; // dll 로드
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// udp 소켓 생성
	SOCKET mulsock = socket(AF_INET, SOCK_DGRAM, 0); // ipv4, socket dataGRAM, option
	if (mulsock == INVALID_SOCKET) { // 실패 시 예외 처리
		printf("SOCKET ERROR!\n");
		return -1;
	}

	// 멀티캐스트 TTL 값
	int multtl = 32; // 설정할 ttl 값 저장
	setsockopt(mulsock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&multtl, sizeof(multtl)); // ttl 값 설정
	// socket handle 값, level 값, option 값, char 형태 ttl 값, ttl 값 크기

	// 통신할 대상의 주소 구조체
	SOCKADDR_IN sendaddr; // 주소 구조체 선언
	memset(&sendaddr, 0, sizeof(sendaddr));

	sendaddr.sin_addr.s_addr = inet_addr("233.3.3.3"); // ip address
	sendaddr.sin_port = htons(22222); // port 번호
	sendaddr.sin_family = AF_INET; // ip version

	// 데이터 전송
	int error = 0; // sendto function error check
	_msg msg; // 데이터를 전송할 구조체 선언
	memset(&msg, 0, sizeof(msg)); // 구조체 초기화
	sprintf(msg.q_str, "[질문] 자신이 선호하는 진로는?\n1.프로그래머\n2.네트워크 관리자\n3.시스템 관리자\n4. 정보보안 관리자");
	// 구조체 내부에 보낼 데이터 저장
	printf("%s", msg.q_str); // 데이터 저장 확인

	error = sendto(mulsock, (char*)&msg, sizeof(msg), 0, (SOCKADDR*)&sendaddr, sizeof(sendaddr)); // 데이터 전송
	// socket handle 값, 보낼 데이터, 데이터의 크기, option, 상대의 주소 구조체, 주소 구조체 크기
	if (error == SOCKET_ERROR) { // sendto error 발생 시 예외 처리
		printf("SENDTO FUNCTION ERROR\n");
		return -1;
	}

	// 통신 대상 주소 구조체
	SOCKADDR_IN recvaddr; // 상대방의 주소를 저장할 구조체
	int recvlen = sizeof(recvaddr); // 주소 구조체 크기 저장

	// 데이터 수신
	int total[5]; // 데이터를 받을 공간
	memset(total, 0, sizeof(total)); // 공간 초기화

	printf("\n### 설문 조사 결과 ###\n");

	int rcvtime = 5000; // receive time out 값 설정 => 5 초 동안만 소켓을 기다리다 안오면 종료
	setsockopt(mulsock, SOL_SOCKET, SO_RCVTIMEO, (char*)&rcvtime, sizeof(rcvtime));
	// socket handle 값, level 값, option 값, char 형태의 timeout 설정값, 설정값의 크기

	while (1) // break 만나기 전까지 반복
	{
		error = recvfrom(mulsock, (char*)&msg, sizeof(msg), 0, (SOCKADDR*)&recvaddr, &recvlen);
		if (error == SOCKET_ERROR) // 잘못된 수신 혹은 time out 발생 시 break
			break;

		if (msg.a_num >= 1 && msg.a_num <= 4) { // 수신값 확인 후
			total[msg.a_num]++; // 데이터 저장 공간에 저장
		}
	}

	// 설문 조사 종료 시
	for (int i = 1; i < 5; i++)
		printf("%d번 : %d명\n", i, total[i]); // 결과값 출력

	// socket dll 종료
	closesocket(mulsock);
	WSACleanup();

	return 0;
}