#pragma once
#include "TaskManager.h"
#include "framework.h"
#include "Time.h"
#include "TimeManager.h"
#include <time.h>
#include "InterWindowController.h"
#include "WindowW.h"
#include <thread>
#include <chrono>

//Timers 
#define Timer_General_ID 5001 // starts with program, generate time till sleep over
#define Timer_Clock_ID 5002 
#define Timer_Display_ID 5003
#define Timer_OneSec_Endless 5011


class TimerWindow : public WindowW
{
	bool active = true; // on exit flag to terminate thread
	thread *threadActivityCounter;
	HWND main, clock, activivty_time, workTime, maxWT, test;
	HWND general;
	void Display(HWND);
	TimeManager* timeManager;
	TIMERPROC proc;
	InterWindowController *controller;
	
public:
	TimerWindow(TimeManager& timeManager, InterWindowController&); // One tm with data General Time/ Work Time
	~TimerWindow();
	void setData(TIMERPROC);
	void CreateTimeWindow(HWND);
	void ClockRun();
	void TimerRun();
	void DailyRun();
	void StartTimer();

	void update();

	void countingActivivtyThread();
	thread* getThread();
	void liquidateActivityThread();
};

