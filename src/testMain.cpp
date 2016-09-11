#include "ProtocolHandler.h"
#include "ioFunc.h"
#include "OrderPackage.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

void testOrderPackage(string frame)
{
	OrderPackage op;
	op.setValue(frame);
	ProtocolHandler::printFrame(op.ToString());
}

void testProtocolHandler()
{
	ProtocolHandler ph;
	unsigned char p[45];
	p[0] = 'E';
	p[1] = 'F';
	p[2] = '#';
	p[3] = '$';
	p[44] = 'E';
	p[43] = 'F';
	p[42] = '#';
	p[41] = '$';
	unsigned char v=0x00;
	for(int i = 4;i!=41;++i)
	{
		p[i]=v++;
	}
	std::string str;
	str = ph.ucharArrayToString(p,45);
	ph.setPackage(str);
	ph.analyze();
	str = ph.getPackage();
	std::vector<std::string> vstr;
	vstr = ph.getFrames();
	std::string s = vstr[0];
	ph.printFrame(s);
	testOrderPackage(s);
}



void testIOFunc()
{
	vector<string> v;
	v=readConfig("Server.config");
	ServerConfig sc;
	int r=sc.ParseConfig(v);
	if(r==0)
	{
		cout<<sc.port<<":"<<sc.Max_Clients<<":"<<sc.Buffer_Size<<endl;
	}
	else
	{
		cout<<"ParseConfig Error."<<endl;
	}
	
}

int main()
{
	//testIOFunc();
	testProtocolHandler();
	return 0;
}