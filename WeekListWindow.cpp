#include "WeekListWindow.h"

WeekListWindow::WeekListWindow()
{
	//tasks = tmanager.getTasksWeek(&this->size);

}

WeekListWindow::~WeekListWindow()
{
	delete[] tasks;
}

void WeekListWindow::createList(HWND w)
{
	week = CreateWindowW(L"General", L"", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 300, 500,
		w, 0, 0, 0);
	addButton = CreateWindowExA(1, "button", "Add task", WS_CHILD | WS_VISIBLE, 10,5, 290, 50,
		week
	, (HMENU)ON_ADD_BUTTON,0,0);
	this->tasks = this->tmanager.getTasksWeek(&this->size);

	this->createScrollList();
}

void WeekListWindow::createScrollList()
{
	dynamicHeight = size * 50 + size + 20;
	scroll = CreateWindowExA(1, "General", "", WS_CHILD | WS_VISIBLE, 10, 105, 290, 390, 
		week, 0, 0, 0);
	list  = CreateWindowExA(1, "static", "", WS_CHILD | WS_VISIBLE, 10, 1, 290, dynamicHeight,
		scroll, 0, 0, 0);

	HWND* subwindows = new HWND[5]; int y = 1;
	for (int i = 0; i < size; i++) {

		HWND element = CreateWindowExA(1, "static", "", WS_CHILD | WS_VISIBLE, 
			1, y, 290, 50, list, 0, 0, 0);
		this->tasks[i].setWindow(element);

		std::string str = std::to_string(this->tasks[i].getPriority());
		subwindows[0] = CreateWindowExA(1, "static", str.c_str(), WS_CHILD | WS_VISIBLE,
			17, 10, 30, 30, element, 0, 0, 0);

		str = this->tasks[i].getTitle();
		subwindows[1] = CreateWindowExA(1, "static", str.c_str(), WS_CHILD | WS_VISIBLE,
			64, 10, 100, 30, element, 0, 0, 0);

		subwindows[2] = CreateWindowExA(1, "static", "To TodatList", WS_CHILD | WS_VISIBLE,
			181, 10, 45, 30, element, 0, 0, 0);

		subwindows[3] = CreateWindowExA(1, "button", "Remove", WS_CHILD | WS_VISIBLE,
			243, 10, 45, 30, element, 0, 0, 0);
		y += 51;
		this->tasks[i].setSubWindows(subwindows, 5);
	}
}
