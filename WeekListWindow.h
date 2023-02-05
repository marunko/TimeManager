#pragma once

#include "framework.h"
#include "TaskManager.h"


#define ON_ADD_BUTTON 1200


class WeekListWindow
{
	HWND week;
	HWND scroll, list, addButton;
	TaskManager tmanager;
	int size, dynamicHeight;
	Task* tasks;

public:
	WeekListWindow();
	~WeekListWindow();
	void createList(HWND);
	void createScrollList();


	void OnWeeklyCommand();
};

