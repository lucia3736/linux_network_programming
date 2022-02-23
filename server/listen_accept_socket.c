//서버의 특정 IP, 특정 포트로 들어오는 연결을 수락하고 데이터를 수신한다.
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
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;

	//소켓 생성
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1) {
		printf("Could not create socket.\n");
	}

	//server.sin_addr.s_addr = inet_addr("142.251.42.142"); //google.com IP 
	server.sin_addr.s_addr = inet_addr("127.0.0.1");;
	server.sin_family = AF_INET;
	server.sin_port = htons(2314); //80 포트에서 들어오는 연결을 확인할 것이다.

	//소켓을 특정 IP주소와 특정 포트번호에 묶는다.(bind)
	//이렇게 하면 이 포트 번호로 향하는 모든 수신 데이터가 이 애플리케이션에서 수신된다.
	if(bind(socket_desc,(struct sockaddr *)&server, sizeof(server)) < 0) {
		puts("bind fail");
		return 1;
	}
	puts("bind success");

	//소켓에서 들어오는 연결 수신 대기
	listen(socket_desc, 3); //연결요청 대기 큐의 크기 : 3
	
	//연결 수락 및 수신
	puts("Waiting for incoming connections ... ");
	c = sizeof(struct sockaddr_in);
	//accept함수에서 반환된 new_socket 소켓은 문지기 역할을 하는데,
	//연결 요청을 한 클라이언트 소켓과 자동으로 연결된다.
	new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);

	if(new_socket < 0) {
		perror("accept failed");
		return 1;
	}
	
	puts("connnection accepted");
		
	return 0;
}
