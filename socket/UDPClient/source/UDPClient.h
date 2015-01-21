#ifndef __UDPCLIENT_H__
#define __UDPCLIENT_H__
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
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

class UDPClient
{
	public:
		UDPClient();
		UDPClient(int port);
		UDPClient(string ipAddr, int port = SERVERPORT);
		void InitIP(string ip,int port=SERVERPORT);
		int InitHostName(string hostname,int port=SERVERPORT);
		int sendMsg(string buf);
		int broadCast(string buf);
		void printAddrInfo();
		void closeUDP();
	private:
		struct sockaddr_in m_sockAddr;
		int m_socketID;
		string m_buf;
	
};

#endif
