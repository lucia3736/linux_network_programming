//소켓을 서버에 연결하고 데이터를 전송한다.
#include <stdio.h>
#include <string.h>
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
	char *message, server_reply[2000];

	//소켓 생성
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1) {
		printf("Could not create socket.\n");
	}

	server.sin_addr.s_addr = inet_addr("142.251.42.142"); //google.com IP 
	server.sin_family = AF_INET;
	server.sin_port = htons(80); 

	//서버에 연결
	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
		puts("connect error");
		return 1;
	}

	puts("Connected");

	//데이터 전송
	message = "GET / HTTP/1.1\r\n\r\n"; //웹사이트의 메인 페이지를 가져오는 http 명령
	if(send(socket_desc, message, strlen(message), 0) < 0) {
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

	//서버로부터 응답 수신
	if(recv(socket_desc, server_reply, 2000, 0) < 0) {
		puts("Receive failed");
		return 1;
	}
	puts("Data Received\n");
	puts(server_reply);

	return 0;
}
