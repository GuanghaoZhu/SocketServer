#include "TcpServer.h"
//应该是建立通道，与具体业务无关。

void TcpServer::setPort(int iPort)
{
	_port=iPort;
}

void TcpServer::setMaxConnNum(int iConnNum)
{
	_maxConnNum=iConnNum;
}

TcpServer::TcpServer(int port)
{
	_port=port;
	_maxConnNum=10;
}

TcpServer::TcpServer(int port,int maxConn)
{
	_port=port;
	_maxConnNum=maxConn;
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
	unsigned char buff[1024];
	
	while((n=recv(*sock,buff,1024,0))>0)
	{
		buff[n]= '\0';
		cout<<"[Received]"<<buff<<endl;	
		ProtocolHandler ph;
		string phStr=ph.ucharArrayToString(buff,n);
		ph.setPackage(phStr);
		if(ph.analyze()==0)
		{
			vector<string> vstr=ph.getFrames();
			for(int i = 0 ;i!=vstr.size();++i)
			{
				cout<<"[FRAME]: "<<i+1<<endl;
				ph.printFrame(vstr[i]);
				cout<<endl;
			}
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

int TcpServer::stop(){};

int TcpServer::start()
{
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
	server_addr.sin_port = htons(_port);
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
	listenRes = listen(sockfd,_maxConnNum);
	if (listenRes!=0)
	{
		cout<<"Listen socket error!Error Code:"<<errno<<endl;
		close(sockfd);
		return 0;
	}
	else
	{
		cout<<"Server is listening...PORT:"<<_port<<endl;
	}
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
}