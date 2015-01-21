#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>//socket
#include <sys/types.h>
#include <netinet/in.h>//sockaddr_in
#include <netdb.h> //gethostbyname()
#include <string.h> //strlen()
#include <unistd.h> //close()
#include <arpa/inet.h> //inet_ntoa()
#define SERVERPORT 3333
#define MAXSIZE 100
using namespace std;

int main(int argc, char *argv[])
{
	cout << "This is UDP Server!" << endl;	
	struct sockaddr_in server_addr, client_addr;
	struct hostent *host;//to get hostname->ip addr
	//host = gethostbyname("localhost");
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVERPORT);	
	cout << SERVERPORT << endl;
	cout << server_addr.sin_port << endl;
	cout << ntohs(server_addr.sin_port) << endl;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);//SOCK_DGRAM uses UDP
	
	bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
	char revBuf[MAXSIZE];
	socklen_t sockAddrLen = sizeof(struct sockaddr_in);
	recvfrom(sockfd, revBuf, MAXSIZE, 0, (struct sockaddr *)&server_addr, &sockAddrLen);
	cout << "get msg::" << revBuf << endl;
	 cout << "from IP:" << inet_ntoa(server_addr.sin_addr) << endl;
	cout << "from port:" << ntohs(server_addr.sin_port) << endl;
	close(sockfd);
	
	
	return 0;
}
