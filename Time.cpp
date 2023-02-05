#include "Time.h"
// copy from Timer 
std::string Time::to_timeFormat()
{
	int hour = mlsTime / 3600000;
	int min = (mlsTime - (hour * 3600000)) / 60000;
	int sec = ((mlsTime - (hour * 3600000)) - (min * 60000)) / 1000;
	int mils = (((mlsTime - (hour * 3600000)) - (min * 60000))) - (sec * 1000);
	std::string str = "" + std::to_string(hour) + ':' + std::to_string(min) + ':'
		+ std::to_string(sec) + ':' + std::to_string(mils);
	return str;
}

std::wstring Time::to_timeFormatW()
{
	long tm = mlsTime / 1000;
	int hour = tm / 3600;
	int min = (tm - (hour * 3600)) / 60;
	int sec = ((tm - (hour * 3600)) - (min * 60));
	int mils = (((tm - (hour * 3600)) - (min * 60))) - (sec);
	std::wstring str = L"" + std::to_wstring(hour) + L':' + std::to_wstring(min) + L':'
		+ std::to_wstring(sec) + L':' + std::to_wstring(mils);
	return str;
}

long Time::to_MlsFormat(std::string)
{
	return 0;
}


long Time::getTimeMls()
{
	return this->mlsTime;
}

void Time::setTimeMls(long mls)
{
	this->mlsTime = mls;
}

long Time::secondDown(short s)
{
	
	return this->mlsTime-=(s*1000);
}

Time::Time()
{
}

Time::Time(long l)
{
	this->mlsTime = l;
}


