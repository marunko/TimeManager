#pragma once
#include <nlohmann/json.hpp>
#include "JsonFileParser.h"
#include "Task.h"
#include <fstream>
struct TaskF {
	short id;
	short priority;
	std::string title;
	std::string description;
	long time;
};
class TaskService
{
	// JsonFileParser jsp;
	// oparates with files 
	// save to files info or take it
	//JsonFileParser fileParser;// ?? do we need this class for json

public:
	TaskService();

	Task* loadTasks(int*, std::string);
	int getSizeArrayTask(std::string);
	Task loadTaskById(int, std::string);
	bool saveTask(Task &task, std::string);
	bool saveTasks(int size, Task *tasks, std::string);

	bool removeTask(short, std::string);
	nlohmann::json setData(Task& task);
 

};

