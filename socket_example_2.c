//인터넷 소켓 주소 생성
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> 

/*
 * <sys/socket.h>, <netinet/in.h> 내 정의되어있는 주요 구조체
 *
 * struct sockaddr_in {
 *	//인터넷 전용 소켓 주소 구조체
 *	short		sin_family;	// 소켓 주소 체계(AF_INET, AF_INET6, ...)
 *	unsigned short	sin_port;	// 포트번호
 *	struct in_addr	sin_addr;	// IP 주소
 *	char		sin_zero[8];
 *};
 *struct in_addr {
 *	unsigned long	s_addr;
 *};
 *struct sockaddr {
 *	unsigned short	sa_family;	// address family, AF_XXX
 *	char		sa_data[14];	// 프로토콜 주소(14바이트)
 *};
*/

int main(int argc, char **argv)
{
	int socket_desc;
	struct sockaddr_in server;

	//소켓 생성
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1) {
		printf("Could not create socket.\n");
	}

	server.sin_addr.s_addr = inet_addr("74.125.235.20");
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//서버에 연결
	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
		puts("connect error");
		return 1;
	}

	puts("Connected");
	return 0;
}
