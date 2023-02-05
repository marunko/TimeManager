#pragma once
#include "Task.h"
#include "Time.h"
#include "TaskService.h"

class TaskManager // holds times, manage
{
private: 
	std::string pathToday = "./files/today.json";
	std::string pathTomorrow = "./files/tomorrow.json";
	std::string pathWeek = "./files/week.json";

	TaskService service; // operates with json files DB
public:
	Task* getTasks(int *); // use service to take tasks from file
	int getSize();

	// Call from TaskList and TimerWindow
	Task getATaskById(int);

	Task* getTasksToday(int*);
	Task* getTasksTomorrow(int*);
	Task* getTasksWeek(int*);

	Task getATaskTodayById(int);
	Task getATaskTomorrowById(int);
	Task getATaskWeekById(int);
	//remove, add, update task
	 
	bool saveAllTasksToday(int, Task* t);

	bool saveNewTaskToday(Task& task);
	bool saveNewTaskTomorrow(Task& task);
	bool saveNewTaskWeek(Task& task);

	bool removeTaskToday(short id);

	// logic 
	bool saveNewTask(Task& task);
	// time manager 
	bool isWorkingTimeAvailable( Time, Time&);
	// 
	bool isTomorrowAvailable(Time&);
	bool isWeekFree();

};

