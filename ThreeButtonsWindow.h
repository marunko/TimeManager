#pragma once
#include "framework.h"
#include <iostream>
#include "WindowW.h"
#include "InterWindowController.h"
#include "resource.h"
#include "TimeManager.h"
#include "WeekListWindow.h"

#define Add_task_button 1200
#define Tomorrow_task_button 1201
#define Weekly_task_button 1202
// add weekly tomorrow
INT_PTR CALLBACK ThreeButtonsProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
class ThreeButtonsWindow : public WindowW
{
	InterWindowController* controller;
	TimeManager* timeManager;
	HWND parentGeneral, thisButtonsWindow;
	HINSTANCE hinstance;
	INT_PTR proc;

	WeekListWindow week;
	// button size
	int bwidth = 260, bheight = 40, margin_left = 30, margin_top = 5;
public:
	ThreeButtonsWindow(InterWindowController&, TimeManager&);

	void CreateThreeButtonsWindow(HWND&);
	void OnButtonCommand(HWND& w, WPARAM wp);
	void setInstance(HINSTANCE&);
	void setProcess(INT_PTR);

	void OnAboutCommand(HWND& w, WPARAM wp);
	void OnAboutCreate(HWND& w, WPARAM wp);
	void OnTomorrowCommand(HWND& w, WPARAM wp);
	void OnWeeklyCommand(HWND& w, WPARAM wp);


};

