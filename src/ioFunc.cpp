#include "ioFunc.h"



using namespace std;
vector<std::string> readConfig(string path)
{
	vector<std::string> res;
	ifstream ifIn(path.c_str());
	
	string tmpStr;
	while(getline(ifIn,tmpStr))
	{
		res.push_back(tmpStr);
	}
	ifIn.close();
	return res;
}


int ServerConfig::ParseConfig(vector<string> vconfig)
{
	if(vconfig.size()!=0)
	{
		for(int i=0;i!=vconfig.size();++i)
		{
			string tmpStr=vconfig[i];
			string name,value;
			int m,n;
			for(int j=0;j!=tmpStr.size();++j)
			{
				switch(tmpStr[j])
				{
					case '=':
						m=j;
						break;
					case ';':
						n=j;
						break;
					default:
						continue;
						break;
				}
				
			}
			name=tmpStr.substr(0,m);
			value=tmpStr.substr(m+1,n-m-1);
			if(name=="PORT")
			{
				port=atoi(value.c_str());
			}
			else if(name=="Max_Clients")
			{
				Max_Clients=atoi(value.c_str());
			}
			else if(name=="Buffer_Size")
			{
				Buffer_Size=atoi(value.c_str());
			}
			else
			{
				//Do Nothing.
			}
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

