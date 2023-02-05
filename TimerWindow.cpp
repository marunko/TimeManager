#include "TimerWindow.h"

void TimerWindow::Display(HWND wind)
{

	// One time call
	this->general = wind;
	main = CreateWindowExA(1, "General", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 20, 25,
		900, 200, wind, 0, 0, 0);
	//sum of TT
	workTime = CreateWindowExA(1, "static", this->timeManager->getWorking_Time().to_timeFormat().c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE, 50, 50,
		75, 50, main, 0, 0, 0);
	CreateWindowExA(1, "static", "|", WS_BORDER | WS_CHILD | WS_VISIBLE, 125, 50,
		20, 50, main, 0, 0, 0);
	maxWT = CreateWindowExA(1, "static", "0:8:0:0", WS_BORDER | WS_CHILD | WS_VISIBLE, 130, 50,
		75, 50, main, 0, 0, 0);
	
	activivty_time = CreateWindowExA(1, "static", this->timeManager->getDaily_Activity_Left().to_timeFormat().c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE, 400, 50,
		75, 50, main, 0, 0, 0);	
	test = CreateWindowExA(1, "static", "some text here", WS_BORDER | WS_CHILD | WS_VISIBLE, 300, 100,
		100, 50, main, 0, 0, 0);

	time_t now = time(0);
	tm* ltm = localtime(&now);
	std::string str = std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min)
		+ ":" + std::to_string(ltm->tm_sec);
	clock = CreateWindowExA(1, "static", str.c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE, 600, 50,
		75, 50, main, 0, 0, 0);
	SetTimer(this->general,             // handle to main window 
		Timer_Clock_ID,    // timer identifier 
		500,                 // 1-second interval 
		(TIMERPROC)proc);
	/*
	SetTimer(this->general,             // handle to main window 
		Timer_OneSec_Endless,    // timer identifier 
		1000,                 // 1-second interval 
		(TIMERPROC)proc); */

	if (this->timeManager->getDaily_Activity_Left().getTimeMls() > 0) {
		SetTimer(this->general,             // handle to main window 
			Timer_On_Activity,    // timer identifier 
			1000,                 // 1-second interval 
			(TIMERPROC)proc);
	}
	threadActivityCounter = new thread(&TimerWindow::countingActivivtyThread, this);
}

TimerWindow::TimerWindow(TimeManager& timeManager, InterWindowController& contr)
{
	this->controller = &contr;
	
	this->timeManager = &timeManager;
	this->controller->addWindowToList("TimerWindow", *this);

}

TimerWindow::~TimerWindow()
{
	delete threadActivityCounter;
}

void TimerWindow::setData(TIMERPROC pr)
{
	this->proc = pr;
}

void TimerWindow::CreateTimeWindow(HWND w)
{
	this->Display(w);

}

void TimerWindow::ClockRun()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	std::wstring str = std::to_wstring(ltm->tm_hour) + L":" + std::to_wstring(ltm->tm_min)
		+ L":" + std::to_wstring(ltm->tm_sec);
	SetWindowText(clock, str.c_str());
}

void TimerWindow::TimerRun()
{ 
	SetWindowText(workTime, timeManager->getWorking_Time().to_timeFormatW().c_str());
}

void TimerWindow::DailyRun()
{
	//MessageBoxA(this->general, "a", "a", 1);
	SetWindowText(activivty_time, timeManager->getDaily_Activity_Left().to_timeFormatW().c_str());
}

void TimerWindow::update()
{
	 
	SetWindowText(workTime, timeManager->getWorking_Time().to_timeFormatW().c_str());
}

void TimerWindow::countingActivivtyThread()
{
	int i = 0;
	timeManager->resetActTime();
	while (active && timeManager->getDaily_Activity_Left().getTimeMls() > 0 ) {
		//timeManager->countingDownDaily_Activity();
		timeManager->resetActTime();
		// recalculate one time in 1-5 min
		//MessageBoxA(this->general, "a", "a", 1);
		/* 
		if (i++ >= 60) {
			timeManager->resetActTime();
			i = 0;
		}*/
		this_thread::sleep_for(chrono::microseconds(500));
	}
}

thread* TimerWindow::getThread()
{
	return this->threadActivityCounter;
}

void TimerWindow::liquidateActivityThread()
{
	// kills thread 
	this->active = false;
}
