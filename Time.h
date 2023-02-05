#pragma once
#include <string>
class Time
{
	long mlsTime;

public:
	std::string to_timeFormat();
	std::wstring to_timeFormatW();
	long to_MlsFormat(std::string);

	long getTimeMls();
	void setTimeMls(long);

	long secondDown(short);
 
	Time();
	Time(long);
	//Time& operator=(Time&);
};

