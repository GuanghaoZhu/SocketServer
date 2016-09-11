#include "main.h"

int main()
{
	vector<string> v;
	v=readConfig("Server.config");
	ServerConfig sc;
	int r=sc.ParseConfig(v);
	if(r==0)
	{
		//cout<<sc.port<<":"<<sc.Max_Clients<<":"<<sc.Buffer_Size<<endl;
		TcpServer server=TcpServer(sc.port,sc.Max_Clients);
		server.start();
	}
	else
	{
		cout<<"ParseConfig Error."<<endl;
	}
	
	return 0;
}