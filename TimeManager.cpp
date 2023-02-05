#include "TimeManager.h"

TimeManager::TimeManager()
{
	//Working_Time.setTimeMls(0);
	this->From = Time(10800000); // 3am next date
	//Daily_Activity_Left.setTimeMls(28800000);
	this->DefaultSettings();

}

void TimeManager::DefaultSettings()
{
	this->setMAX_Working_Time(28800000);
	this->setOne_Task_Time_Min(600000);
	this->setOne_Task_Time_Max(14400000);
}

void TimeManager::countingDown()
{
	Working_Time.setTimeMls(Working_Time.getTimeMls()-500);
}

void TimeManager::countingDownDaily_Activity()
{
	 
	Daily_Activity_Left.setTimeMls(Daily_Activity_Left.getTimeMls() - 500);
}

void TimeManager::setActivityHours(Time& from, Time& to)
{
	this->From = from;
	this->To = to;
}

void TimeManager::setWorking_Time(long mls)
{
	Working_Time.setTimeMls(mls);
}

void TimeManager::setMAX_Working_Time(long mls)
{
	return this->MAX_Working_Time.setTimeMls(mls);
}

void TimeManager::setOne_Task_Time_Min(long mls)
{
	this->One_Task_Time_Min.setTimeMls(mls);
}

void TimeManager::setOne_Task_Time_Max(long mls)
{
	this->One_Task_Time_Max.setTimeMls(mls);
}

Time TimeManager::getDaily_Activity_Left()
{
	return this->Daily_Activity_Left;
}

Time TimeManager::getWorking_Time()
{
	return this->Working_Time;
}

Time TimeManager::getMAX_Working_Time()
{
	return this->MAX_Working_Time;
}

Time TimeManager::getOne_Task_Time_Min()
{
	return this->One_Task_Time_Min;
}

Time TimeManager::getOne_Task_Time_Max()
{
	return this->One_Task_Time_Max;
}

void TimeManager::OnAppStart()
{
	TimeOut t = tservice.loadsavedDate();
	time_t now = time(0);
	// last visit date + time left + 8 hours are bigger than now - start new session
	long long l = t.date; //28800;
	l += 28800;
	l += t.activityTLeft;
	if (l < now) {
		// NewSession
		this->NewSession(now);
	}
	else {
		// old session
		this->OldSession(t.activityTLeft, now,t.date);
	}

}
// call onAppDestroy in cases: exit, outOfActivityTime (:Timer)
void TimeManager::OnAppDestroy()
{
 

	// compare file actTleft and current 
	// if act time left == 0  then you are working in resting time 
	// then dont save anything to file 
	if (this->Daily_Activity_Left.getTimeMls() <= 0) {
		return;
	}
	else {
		time_t now = time(0);
		TimeOut t = {
			now,
			this->Daily_Activity_Left.getTimeMls()/1000 };
		tservice.saveDate(t);
	}
	// else save info now and act time
}
bool TimeManager::isOutOfActivityTime(HWND w)
{
	if (Daily_Activity_Left.getTimeMls() <=0) {
		time_t now = time(0);
		TimeOut t = {
			now,
			0 };
		tservice.saveDate(t);
		// Kill thread
		KillTimer(w, Timer_On_Activity); //View timer in Display(); StartTimer
		return true;
	}
	return false;
}
Time TimeManager::timeParseFromString(std::string hh, std::string mm)
{
	long n1 = 0;
	long n2 = 0;
	if(hh.size()>0)
		n1 = stol(hh);
	if (mm.size() > 0)
		n2 = stol(mm);

	return Time(((n1*3600) + (n2*60))*1000);
}
//outOfActivityTime (:Timer) when time out during session - save last info to file
// 1.last-date-enter = current time 2. AT left = 0

//	!!!!!!!!!!!!!!!!!!
void TimeManager::NewSession(time_t& now)
{
	// set new session 
	// set To 
	tm* ltm = localtime(&now);
	int max27 = 27 * 3600;
	int anHourInSec = (ltm->tm_hour * 3600) + (ltm->tm_min*60) + (ltm->tm_sec);
	int constantHours = 14 * 3600;
	if (max27 > anHourInSec + constantHours) {
		long t = 50400000; // 14h
		Daily_Activity_Left.setTimeMls(t);
		//this->maxTime = 50400 + now;
	}
	else { 
		long t = (max27 - anHourInSec)*1000;  
		Daily_Activity_Left.setTimeMls(t);
	}
}

void TimeManager::OldSession(long& pastActivityTimeLeft, time_t& now, long& pastDate)
{
	// set old session 
	int day = 86400; // sec
	// if enter out of free time left
	long finish_time_from_prev_fixed = pastActivityTimeLeft + pastDate;

	// 8am + 14 AT = 22pm or 14pm + 8 AT = 22pm
	// now is <22pm - we still are in time if now is >22pm like 23pm we are out of AT
	if (pastActivityTimeLeft <= 0) {
		Daily_Activity_Left.setTimeMls(0);
		return;
	}
	if (finish_time_from_prev_fixed < now) {
		Daily_Activity_Left.setTimeMls(0);
		return;
	}
	// if now < ft
	tm* ltm = localtime(&now);
	int anHourInSec = (ltm->tm_hour * 3600) + (ltm->tm_min * 60) + (ltm->tm_sec);
	long newActTimeLeft = (27 * 3600) - anHourInSec; // minus time when y was out of session 
	//long newActTimeLeft = finish_time_from_prev_fixed - now; // minus time when y was out of session 
	long long t = (newActTimeLeft) * 1000;
	 
	Daily_Activity_Left.setTimeMls(t); // this time is not correnct on seconsds 
}

void TimeManager::resetActTime()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int anHourInSec = (ltm->tm_hour * 3600) + (ltm->tm_min * 60) + (ltm->tm_sec);
	long newActTimeLeft = (27 * 3600) - anHourInSec; // minus time when y was out of session 
	//long newActTimeLeft = finish_time_from_prev_fixed - now; // minus time when y was out of session 
	long long t = (newActTimeLeft) * 1000;

	Daily_Activity_Left.setTimeMls(t); // this time is not correnct on seconsds 
}

DWORD __stdcall ActivityCountThread(LPVOID lpParameter)
{

	return 0;
}
