#include "UDPServer.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <iostream>
//#include <sys/socket.h>//socket
//#include <sys/types.h>
//#include <netinet/in.h>//sockaddr_in
//#include <netdb.h> //gethostbyname()
//#include <string.h> //strlen()
//#include <unistd.h> //close()
//#include <arpa/inet.h> //inet_ntoa()
using namespace std;

UDPServer::UDPServer()
{
	cout << "UDPServer:UDPServer()" << endl;	
	memset(&m_sockAddr,0,sizeof(struct sockaddr_in));
	m_socketID = socket(AF_INET, SOCK_DGRAM, 0); 
	m_buf = "";
	//initialize m_sockAddr

	m_sockAddr.sin_family = AF_INET;
	m_sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_sockAddr.sin_port = htons(SERVERPORT);
}
 
UDPServer::UDPServer(string ip,int port) 
{
	 InitIP(ip, port);
}

void UDPServer::InitIP(string ip, int port)
{
	memset(&m_sockAddr, 0, sizeof(struct sockaddr_in));
	m_sockAddr.sin_family = AF_INET;
	m_sockAddr.sin_addr.s_addr = inet_addr(ip.c_str());
	m_sockAddr.sin_port = htons(port); 
}
int UDPServer::InitHostName(string hostname, int port)
{
	memset(&m_sockAddr, 0 ,sizeof(struct sockaddr_in));
	struct hostent *host;
	if(NULL == (host=gethostbyname(hostname.c_str())))
	{
		fprintf(stderr,"can not find ip of :%s",hostname.c_str());
		return -1;
	}
	else
	{
		m_sockAddr.sin_addr = *((struct in_addr *)host->h_addr);
		m_sockAddr.sin_port = port;
		m_sockAddr.sin_family = AF_INET;
	}
	if(NULL != host)
	{
		delete host;
		host = NULL;
	}
	return 0;
}

int UDPServer::bindSocket()
{
	
	if(-1==bind(m_socketID, (struct sockaddr*)&m_sockAddr,sizeof(struct sockaddr_in)))
	{
		fprintf(stderr,"can not bind socket of");
		return -1;
	}
	return 0;
}

void UDPServer::receiveMsg(string& revMsg)
{
	char revBuf[MAXSIZE];
	socklen_t sockAddrLen = sizeof(struct sockaddr_in);
	recvfrom(m_socketID, revBuf, MAXSIZE, 0, (struct sockaddr *)&m_sockAddr, &sockAddrLen);
	revMsg = revBuf;
	m_revBuf = revBuf;
}

int UDPServer::sendMsg(string buf)
{
	m_buf = buf;
	sendto(m_socketID,buf.c_str(),strlen(buf.c_str()),0,(struct sockaddr *)&m_sockAddr, sizeof(struct sockaddr_in));		
}

int UDPServer::broadCast(string buf)
{
	int so_broadcast = 1;
	m_sockAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	setsockopt(m_socketID, SOL_SOCKET,SO_BROADCAST, &so_broadcast, sizeof(so_broadcast));
	sendMsg(buf);
}

void UDPServer::printAddrInfo()
{
	cout << "From IP:" << inet_ntoa(m_sockAddr.sin_addr) << endl;
	cout << "From port:" << htons(m_sockAddr.sin_port)<< endl;
	cout << "inet_addr:" << htonl(m_sockAddr.sin_addr.s_addr) << endl;
	cout << "msg:" << m_revBuf << endl;
}
void UDPServer::closeUDP()
{
	close(m_socketID);
}
/*
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
	int sockfd 	= socket(AF_INET, SOCK_DGRAM, 0);
	int so_broadcast = 1;
	setsockopt(sockfd, SOL_SOCKET,SO_BROADCAST, &so_broadcast, sizeof(so_broadcast));
	char buf[]="liaohui";
	sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
	cout << "send msg:" << buf << endl;
	cout << "send IP:" << inet_ntoa(server_addr.sin_addr) << endl;
	cout << "send port:" << ntohs(server_addr.sin_port) << endl;	
	close(sockfd);
	
	
	return 0;
}*/