#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <vector>
#include <sstream>

#include "ServerConfig.h"
#include "OrderPackage.h"
#include "ProtocolHandler.h"
#include "ioFunc.h"

using namespace std;
void *thread_Client(void *arg);
int frameCheck(const unsigned char *recvMsg);

bool startWith(unsigned char *str,const string &match)
{
	for(int i = 0;i!=match.size();++i)
	{
		if(*(str+i)==match[i])
		{
			continue;
		}
		else
		{
			return false; 
		}
	}
	return true;
}

//bool endWith(unsigned char *str, )


int main()
{	
	//unsigned char s[] = "EF*$01234567890";
	//cout<<"StartWith:"<<startWith(s,"EF#$")<<endl;
	int sockfd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t sin_size;

	/* Create the Socket */
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	string str = (sockfd!=-1)?"Socket Created.":"Failed to create the Socket.";
	cout<<str<<endl;
	if (sockfd==-1) return 0;
	
	/* Set Server Address Data*/
	int bindRes;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(_PORT);
	//server_addr.sin_addr.s_addr = inet_addr(_HOST.c_str());
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	bzero(&(server_addr.sin_zero),sizeof(server_addr.sin_zero));

	/* Bind the Socket to Address */
	bindRes = bind( sockfd , (struct sockaddr *)&server_addr , sizeof(struct sockaddr));
	str = (bindRes!=-1)?"Bind Success.":"Bind Failed.";
	cout<<str<<endl;
	if (bindRes!=0)
	{
		close(sockfd);
		cout<<"Socket Closed."<<endl;
		return 0;
	}
	
	/* Listening */
	int listenRes;
	listenRes = listen(sockfd,_MAX_CLIENT_NUM);
	if (listenRes!=0)
	{
		cout<<"Listen socket error!Error Code:"<<errno<<endl;
		close(sockfd);
		return 0;
	}
	else
	{
		cout<<"Server is listening...PORT:"<<_PORT<<endl;
	}
	
	vector<int> clients;
	vector<pthread_t> threads;

	while(1)
	{
		/* Accept the Client */	
		int clientfd;
		sin_size = sizeof(struct sockaddr_in);
		clientfd = accept(sockfd,(struct sockaddr*)&client_addr,&sin_size);
		if (clientfd<=0)
		{
			cout<<"Accept Client error."<<endl;
			continue;
		}
		else
		{
			//Get Client Address and Port Number.
			cout<<"Client("<<inet_ntoa(client_addr.sin_addr)<<":"<<client_addr.sin_port<<") Accepted."<<endl;
			pthread_t tid;
			if (pthread_create(&tid,NULL,thread_Client,&clientfd))
			{
				cout<<"Create Thread Error."<<endl;
				
			}
			else
			{
				clients.push_back(clientfd);
				threads.push_back(tid);
				
			}
		}
	}
	return 0;
	
}

void *thread_Client(void *arg)
{
	/* Send Welcome Message */
	int *sock = (int*)arg;
	string msg = "Welcome!";
	int len,bytes_sent;
	len = msg.size();
	bytes_sent = send(*sock,msg.c_str(),len,0);
	string str = (bytes_sent!=-1)?"Message Sent.":"Failed to Send Message.";
	cout<<str<<endl;
	int n;
	unsigned char buff[_RECV_BUFF_SIZE];
	
	while((n=recv(*sock,buff,_RECV_BUFF_SIZE,0))>0)
	{
		buff[n]= '\0';
		cout<<"[Received]"<<buff<<endl;	
		//frameCheck(buff);
		ProtocolHandler ph;
		string phStr=ph.ucharArrayToString(buff,n);
		ph.setPackage(phStr);
		if(ph.analyze()==0)
		{
			vector<string> vstr=ph.getFrames();
			ph.printFrame(vstr[0]);
			string s="Data Received OK.Length=";
			stringstream c;
			c<<n;
			s+=c.str();
			send(*sock,s.c_str(),s.size(),0);
		}
		else
		{
			string s="Data format illegal.Length:";
			stringstream c;
			c<<n;
			s+=c.str();
			send(*sock,s.c_str(),s.size(),0);
		}
		
		
		
		//if(strncmp(buff,"quit",4)==0) break;
	}
	close(*sock);
}

/*
int frameCheck(const unsigned char *recvMsg)//Input one frame.
{
	cout<<"Order Received.Checking:"<<recvMsg<<endl;
	bool headerCheck = (*recvMsg=='E')&&(*(recvMsg+1)=='F')&&(*(recvMsg+2)=='#')&&(*(recvMsg+3)=='$');
	bool endCheck = (*(recvMsg+41)=='$')&&(*(recvMsg+42)=='#')&&(*(recvMsg+43)=='F')&&(*(recvMsg+44)=='E');
	if(headerCheck)
	{
		if(endCheck)
		{
			//Create a vector and invoke setValue function.
			vector<unsigned char> vChar;
			for(int i = 4;i!=39;++i)
			{
				vChar.push_back(*(recvMsg+i));
			}
			
			//Sum Check Function.
			//Do other thing.
		}
		else
		{
			//FrameHeader Check Passed but FrameEnd Check Failed.
			return -1;
		}
	}
	else
	{
		//FrameHeader Check Failed.
		return -1;
	}
}
*/



