#include "ProtocolHandler.h"

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

std::string ProtocolHandler::ucharArrayToString(unsigned char* msg,std::string::size_type array_size)
{
	std::string res;
	for(std::string::size_type i = 0 ; i!=array_size; ++i)
	{
		res.push_back(*(msg+i)); 
	}
	return res;
}

void ProtocolHandler::setPackage(std::string str)
{
	_package = str;
}

std::string ProtocolHandler::getPackage()
{
	return _package;
}


/*ProtocolHandler::analyze()
*   	Return: 
*		0(Success.)
*		-1(Input Length is too short.)
*		-2(Frame Header and End not found.)
*/
int ProtocolHandler::analyze()
{
	if(_package.size()<45)
	{
		return -1;
	}
	else
	{
		int foundNum = 0;//Count Frame Number.
		int res = -2;
		for(int i=0;i!=_package.size();++i)
		{
			if(_package[i]=='E')//Start with 'E' and there's enough space for check.
			{
				if(i<=(_package.size()-45))
				{
					//Space Check ok.
					bool b1 = (_package[i+1]=='F')&&(_package[i+2]=='#')&&(_package[i+3]=='$');
					bool b2 = (_package[i+44]=='E')&&(_package[i+43]=='F')&&(_package[i+42]=='#')&&(_package[i+41]=='$');
					if(b1&&b2)
					{
						std::string tmpStr = _package.substr(i,45);
						_frames.push_back(tmpStr);
						foundNum++;
						res = 0;
						i+=44;
						continue;
					}
					else
					{
						continue;
					}
				}
				else
				{
					break;//Bytes left is less than 45.
				}
			}
			else
			{
				continue;
			}
		}
		return res;
	}
}

std::vector<std::string> ProtocolHandler::getFrames()
{
	return _frames;
}

void ProtocolHandler::printFrame(std::string _fr)
{
	for(int i = 0;i!=_fr.size();++i)
	{
		char ctrlChar;
		std::string tmpS = _fr;
		std::cout<<"["<<std::setbase(10)<<i<<"]:";
		if((i+1)%5==0)
		{
			ctrlChar = '\n';
			std::cout<<"0x"<<std::setbase(16)<<(int)tmpS[i]<<ctrlChar;
		}else
		{
			ctrlChar = '\t';
			std::cout<<"0x"<<std::setbase(16)<<(int)tmpS[i]<<ctrlChar<<ctrlChar;
		}		
	}
	std::cout<<std::endl;
}
