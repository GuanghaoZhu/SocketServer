#ifndef IOFUNC_H
#define IOFUNC_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>


std::vector<std::string> readConfig(std::string path);


struct ServerConfig
{
public:
	int port;
	int Max_Clients;
	int Buffer_Size;
	int ParseConfig(std::vector<std::string>);
};




#endif