#pragma once
#include "framework.h"
#include <iostream>
#include "Time.h"
class Task
{
	HWND window;
	HWND *subWindows;
	short windowsSize;
	short id;
	short priority;
	std::string title;
	std::string description;
	Time timer; // time left before out
	bool counting = false; // ?
	bool active; // ?

public:
	Task(short, short, std::string, std::string, Time);
	Task();
	Task(const Task &other);
	 // operator= and copy constr add here
	Task& operator=(const Task &other);
	// Getters
	
	HWND getWindow();
	HWND getSubWindow(int);
	short getId();
	short getPriority();
	std::string getTitle();
	std::string getDescription();
	Time* getTimer();
	bool isActive();
	bool isCounting();

	//setters
	void setId(int);
	void setCounting(bool);
	void setSubWindows(HWND* w, short);
	void setSubWindow(HWND& w, int i);
	void setWindow(HWND&);

	~Task();

};

