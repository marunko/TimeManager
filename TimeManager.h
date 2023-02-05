#pragma once

#pragma warning(disable : 4996)
#include "Time.h"
#include "framework.h"
#include "TimeService.h"

#define Timer_On_Activity 5013
DWORD WINAPI ActivityCountThread(LPVOID lpParameter);

class TimeManager
{
	TimeService tservice = {"./files/date.json"};
	// current times of timers
	Time task_Performance_Time; // count down timer
	Time Working_Time; // left
	Time Daily_Activity_Left; // check with system time and disable if out of time
	 
    Time MAX_Working_Time; // set max Daily_Activity_Left
	Time From, To;
	long long maxTime;
	Time open_time; 

	Time Daily_Activity_MAX; // 14 hours 
	Time Daily_Activity_MIN; //? 2 hours
	Time One_Task_Time_Min, One_Task_Time_Max;// 10 min to 6 hours
	// when will add new set default 2 hours 
public:
	TimeManager();
	void DefaultSettings();

	void countingDown();//take from task cls
	void countingDownDaily_Activity();//take from task cls
	// setters
	void setActivityHours(Time &from, Time &to);
	void setWorking_Time(long mls);
	void setMAX_Working_Time(long mls);
	void setOne_Task_Time_Min(long mls);
	void setOne_Task_Time_Max(long mls);

	// getters
	Time getDaily_Activity_Left();
	Time getWorking_Time();
	Time getMAX_Working_Time();
	Time getOne_Task_Time_Min();
	Time getOne_Task_Time_Max();
	// logic 
	void OnAppStart();//check what day, reset all data
	void OnAppDestroy();
	bool isOutOfActivityTime(HWND w);
 
	// save date, data, extra activity hours

	bool isWTOutOfTime();// timer check every 10 min is there a time for Work left in Activity time
	Time timeParseFromString(std::string, std::string);
	bool timeStringHMVerify(std::string, std::string);
	bool timeStringFormatVerify(std::string, int);
// if no T left -> move last task to next day stack
	void resetActTime();
private:
	// file 
	void saveTimeDate();
	// check from task manager
	
	// count down task_Performance_Time and Daily_Activity_Left
	bool isItToday();
	// ================================================================================== 
	// ================================  SESSIONS =======================================
	void NewSession();
	void NewSession(time_t& now);
	void OldSession(long& pastActivityTimeLeft, time_t& now, long& pastDate);
	 

	// ================================================================================== 
	// ================================ USER SETTINGS =======================================
	void extendActivityTime();
	void resetTimeTo();
	void resetMaxWorkingTime();
};

