//Socket 생성 코드
#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char **argv)
{
	//포트 번호를 임의지정하기 위해, 원하는 포트번호를 입력으로 받는다.	 
	int sockfd; //socket descriptor
	if(argc < 2) {
		//포트번호가 입력으로 들어오지 않았을 때
		printf("Usage: %s port\n", argv[0]);
		return -1;
	}
	if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		/*
		 * int socket(int domain, int type, int protocol)
		 * 소켓을 생성하는 함수로, 해당 소켓을 가리키는 socket descriptor를 반환한다.
		 *
		 * param : domain (통신할 영역)  
		 * 		- PF_INET / AF_INET : IPv4 주소 체계 사용
		 * 		- PF_INET6 / AF_INET6 : IPv6 주소 체계 사용
		 * 		- PF_LOCAL / AF_LOCAL : 로컬 통신을 위한 UNIX 프로토콜
		 * 	   type (프로토콜 타입)
		 * 		- SOCK_STREAM : 서비스 타입 (TCP) 
		 * 		- SOCK_DGRAM : 서비스 타입 (UDP)
		 * 		- SOCK_RAW : TCP/UDP 계층을 거치지 않고 바로 IP 계층 이용	
		 * 	   protocol (프로토콜 값)
		 *		- IPPROTO_TCP : TCP일 때
		 *		- IPPROTO_UDP : UDP일 때
		 * ret : -1 (소켓 생성 실패)
		 * 	 0 이상의 값(socket descriptor)
		 *
		*/
		perror("Socket failed!");
		return -1;
	}
	
	return 0;
}
