#ifndef _TCPSERVER_H
#define _TCPSERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <vector>
#include <sstream>

#include "ProtocolHandler.h"

using namespace std;
class TcpServer
{
	private:
		int _port;
		int _maxConnNum;
		string::size_type _bufferSize;
		vector<int> clients;
		vector<pthread_t> threads;
		int sockfd;
		struct sockaddr_in server_addr;
	public:
		
		
		TcpServer(int port);
		TcpServer(int port,int maxConn);
		void setPort(int iPort);
		void setMaxConnNum(int iConnNum);
		int start();
		int stop();
};

void *thread_Client(void *arg);

#endif