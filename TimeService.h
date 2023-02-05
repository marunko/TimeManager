#pragma once
#include <string>
#include "Time.h"
#include <fstream>
#include <nlohmann/json.hpp>
struct TimeOut {
	long date;
	long activityTLeft;
};
class TimeService
{
	std::string path;
public:
	TimeService(std::string path);
	TimeService();
	// save close time 
	void saveDate(TimeOut&);

	//load saved time from past load
	TimeOut loadsavedDate();

};

