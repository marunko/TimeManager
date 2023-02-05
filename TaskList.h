#pragma once

#include "framework.h"
#include <iostream>
#include <string>
#include "WindowsTests.h"
#include "WindowW.h"
#include "Task.h"
#include "TaskManager.h"
#include "Time.h"
#include "TimeManager.h"
#include "InterWindowController.h"
#include <thread>
#include <chrono>
#define OnClick 1000
#define OnStart 300
#define OnPause 301

// Timers
#define Timer_TaskTime_ID 5000
#define Display_Timer 5010
 
 
class TaskList : public WindowW
{
	int size, subWindowsSize; //set in 
	//HWND *tasks;
	thread* threadWT;
	HWND main, scroll;
	HWND generalWindow;
	TaskManager tmanager;
	Task *tasks;
	TimeManager* timeManager;
	InterWindowController* controller;
	SCROLLINFO scrollinfo;
//	HANDLE countThread; // counting thread var

	int taskWindowHeight;
	int taskWindowWidth;
	int mainHeight, dynamicHeight;
	void Display(HWND);
	void RemoveAllWindows();
	void moveTaskWindows(int); // move window
	void updateTimeManager();
	void createTaskWindow(int, Task&, int,int);
	//LRESULT CALLBACK TaskProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	WNDCLASS NewWindow(HBRUSH BGcolor, HCURSOR cursor, HINSTANCE instance, HICON icon, LPCWSTR name, WNDPROC proc);
	void destroySubwindows(Task&);

	void changePositionUp(int);
	void changePositionDown(int);
public:
	void createList(HWND);//parse file->create Dynamic arr->display()

	void addTaskToList();//from dialog window, check full time limit (<8 hours)

	void removeTaskFromList(int); // WM_COMMAND button remove
	void updateTaskList(); // updates TL
	void update();

	void OnScrollList(HWND, WPARAM);
	void OnRemoveClick(HWND, WPARAM);
	void OnStartClick(HWND, WPARAM);
	void OnPauseClick(HWND, WPARAM);
	void registerClasses(HINSTANCE);
	void OnChangeOrderClick(HWND, WPARAM);

	// counters 
	void counting();
	void saveTaskCounterOnExit();
	void DisplayCounter();
	thread* getThread();


	TaskList(TimeManager&, InterWindowController&);
	 
	~TaskList();
	//Task time shall not be less then 10 min

};

