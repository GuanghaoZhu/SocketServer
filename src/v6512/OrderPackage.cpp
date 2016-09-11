#include "OrderPackage.h"

#include <iostream>

std::string OrderPackage::ToString()
{
	std::string res;
	res.resize(35);
	res[0] = num;
	res[1] = freqSelect;
	res[2] = outPower[0];
	res[3] = outPower[1];
	res[4] = interfereType;
	res[5] = beginFreq[0];
	res[6] = beginFreq[1];
	res[7] = beginFreq[2];
	res[8] = beginFreq[3];
	res[9] = beginFreq[4];
	res[10] = beginFreq[5];
	res[11] = beginFreq[6];
	res[12] = beginFreq[7];
	res[13] = endFreq[0];
	res[14] = endFreq[1];
	res[15] = endFreq[2];
	res[16] = endFreq[3];
	res[17] = endFreq[4];
	res[18] = endFreq[5];
	res[19] = endFreq[6];
	res[20] = endFreq[7];
	res[21] = freqInterval[0];
	res[22] = freqInterval[1];
	res[23] = freqInterval[2];
	res[24] = freqInterval[3];
	res[25] = freqInterval[4];
	res[26] = freqInterval[5];
	res[27] = freqInterval[6];
	res[28] = freqInterval[7];
	res[29] = modulateType;
	res[30] = interfereWave;
	res[31] = modulateCoefficient[0];
	res[32] = modulateCoefficient[1];
	res[33] = repeatPeriod[0];
	res[34] = repeatPeriod[1];
	
	return res;
}

std::string OrderPackage::ToDetail()
{
	
}

int OrderPackage::setValue(std::string _in)
{
	if(_in.size()==45)
	{
		std::string pkg = _in.substr(4,35);
		num = pkg[0];
		freqSelect = pkg[1];
		outPower[0] = pkg[2];
		outPower[1] = pkg[3];
		interfereType = pkg[4];
		beginFreq[0] = pkg[5];
		beginFreq[1] = pkg[6];
		beginFreq[2] = pkg[7];
		beginFreq[3] = pkg[8];
		beginFreq[4] = pkg[9];
		beginFreq[5] = pkg[10];
		beginFreq[6] = pkg[11];
		beginFreq[7] = pkg[12];
		endFreq[0] = pkg[13];
		endFreq[1] = pkg[14];
		endFreq[2] = pkg[15];
		endFreq[3] = pkg[16];
		endFreq[4] = pkg[17];
		endFreq[5] = pkg[18];
		endFreq[6] = pkg[19];
		endFreq[7] = pkg[20];
		freqInterval[0] = pkg[21];
		freqInterval[1] = pkg[22];
		freqInterval[2] = pkg[23];
		freqInterval[3] = pkg[24];
		freqInterval[4] = pkg[25];
		freqInterval[5] = pkg[26];
		freqInterval[6] = pkg[27];
		freqInterval[7] = pkg[28];
		modulateType = pkg[29];
		interfereWave = pkg[30];
		modulateCoefficient[0] = pkg[31];
		modulateCoefficient[1] = pkg[32];
		repeatPeriod[0] = pkg[33];
		repeatPeriod[1] = pkg[34];
		return 0;
	}
	else
	{
		return -1;
	}
	
}
