#ifndef _ORDERPACKAGE_H
#define _ORDERPACKAGE_H

#include <string>
#include <vector>

struct OrderPackage
{
	unsigned char num;
	unsigned char freqSelect;
	unsigned char outPower[2];
	unsigned char interfereType;
	unsigned char beginFreq[8];
	unsigned char endFreq[8];
	unsigned char freqInterval[8];
	unsigned char modulateType;
	unsigned char interfereWave;
	unsigned char modulateCoefficient[2];
	unsigned char repeatPeriod[2];
	
	std::string ToString();
	std::string ToDetail();
	int setValue(const std::vector<unsigned char> &pkg);
};

#endif