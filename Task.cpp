#include "Task.h"

Task::Task(short id, short priority, std::string title, std::string descritpion, Time time)
{
	this->id = id;
	this->priority = priority;
	this->title = title;
	this->description = descritpion;
	this->timer = time;

	this->active = true;
	this->subWindows = nullptr;
	this->windowsSize = 0;
}

Task::Task()
{
	
}

Task::Task(const Task& other)
{
	this->window = other.window;
	this->id = other.id;
	this->priority = other.priority;
	this->title = other.title;
	this->description = other.description;
	this->timer = other.timer;

	this->active = other.active;
	this->counting = other.counting;

	this->windowsSize = other.windowsSize;
	if (other.subWindows != nullptr){
			this->subWindows = new HWND[windowsSize];
		for (int i = 0; i < windowsSize; i++)
			this->subWindows[i] = other.subWindows[i];
	}
	else { this->subWindows = other.subWindows; }
}

Task& Task::operator=(const Task& other)
{
	this->window = other.window;
	this->id = other.id;
	this->priority = other.priority;
	this->title = other.title;
	this->description = other.description;
	this->timer = other.timer;

	this->active = other.active;
	this->counting = other.counting;

	this->windowsSize = other.windowsSize;
	if (other.subWindows != nullptr) {
		this->subWindows = new HWND[windowsSize];
		for (int i = 0; i < windowsSize; i++)
			this->subWindows[i] = other.subWindows[i];
	}
	else { this->subWindows = other.subWindows; }
	return *this;
}
void Task::setId(int id) {
	this->id = id;
}
void Task::setSubWindow(HWND& w, int i)
{
	this->subWindows[i] = w;
}
void Task::setCounting(bool b)
{
	this->counting = b;
}
void Task::setSubWindows(HWND* wp, short size)
{
	if (subWindows == nullptr) delete[] subWindows;
	this->subWindows = wp;
	this->windowsSize = size;
	 
}
void Task::setWindow(HWND& window)
{
	this->window = window;
}

Task::~Task()
{

	if (subWindows == nullptr) {
		delete[] subWindows;
	}
	 
		  
}

HWND Task::getWindow()
{
	return window;
}

HWND Task::getSubWindow(int i)
{
	return subWindows[i];
}

short Task::getId()
{
	return id;
}

short Task::getPriority()
{
	return priority;
}

std::string Task::getTitle()
{
	return title;
}

std::string Task::getDescription()
{
	return description;
}

Time* Task::getTimer()
{
	return &this->timer;
}

bool Task::isActive()
{
	return active;
}

bool Task::isCounting()
{
	return counting;
}
