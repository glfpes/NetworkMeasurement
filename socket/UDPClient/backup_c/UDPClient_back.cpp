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
	cout << "This is UDP client" << endl;	
	struct sockaddr_in server_addr;
	struct hostent *host;//to get hostname->ip addr
	host = gethostbyname("localhost");
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVERPORT);	
	//server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	//server_addr.sin_addr.s_addr = inet_addr("192.168.1.255");
	server_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	int so_broadcast = 1;
	setsockopt(sockfd, SOL_SOCKET,SO_BROADCAST, &so_broadcast, sizeof(so_broadcast));
	char buf[]="liaohui";
	sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
	cout << "send msg:" << buf << endl;
	cout << "send IP:" << inet_ntoa(server_addr.sin_addr) << endl;
	cout << "send port:" << ntohs(server_addr.sin_port) << endl;
	
	close(sockfd);
	
	
	return 0;
}
