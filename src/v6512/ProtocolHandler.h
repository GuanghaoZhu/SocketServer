#ifndef _PROTOCOLHANDLER_H
#define _PROTOCOLHANDLER_H

#include <vector>
#include <string>

class ProtocolHandler
{
	private:
		std::string _package;
		std::vector<std::string> _frames;
		std::string _log;
		
	public:
		
		void setPackage(std::string str);
		std::string getPackage();
		int analyze();
		std::vector<std::string> getFrames();
		static std::string ucharArrayToString(unsigned char* msg,std::string::size_type array_size);
		static void printFrame(std::string _fr);
		//bool FrameCheck();
};



#endif