//원하는 hostname에 해당하는 IP 주소를 찾아준다.
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

/* 단일 host에 대한 데이터 항목을 나타낸 구조체이다.(netdb.h에 정의되어 있음)
*struct hostent
*{
*  char *h_name;		// host의 공식 이름 
*  char **h_aliases;		// Alias 목록
*  int h_addrtype;		// Host 주소 유형
*  int h_length;		// 주소 길이
*  char **h_addr_list;		// h_name 서버의 주소 목록
*};
*/

int main(int argc, char *argv[])
{
	char *hostname = "www.google.com";
	char ip[100];
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

	//gethostbyname 함수를 통해 도메인 이름을 입력받고, 
	// ip 주소를 포함한 hostent 구조체를 반환한다.
	if((he = gethostbyname(hostname)) == NULL) {
		//gethostbyname 함수 실패
		herror("gethostbyname");
		return 1;
	}

	//h_addr_list가 긴 형식의 IP 주소를 가지고 있기 때문에 in_addr에 h_addr_list를 캐스트한다.
	addr_list = (struct in_addr **)he->h_addr_list;

	for(i=0; addr_list[i] != NULL; i++) {
		//첫 번째 값 반환
		strcpy(ip, inet_ntoa(*addr_list[i]));
	}

	printf("%s -> %s", hostname, ip);
	return 0;
}
