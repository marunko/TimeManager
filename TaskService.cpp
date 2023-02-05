#include "TaskService.h"
using namespace std;
using json = nlohmann::json;
TaskService::TaskService( )
{
  
}
Task* TaskService::loadTasks(int *s, std::string path)
{
    std::ifstream f(path);
    json data = json::parse(f);
    if (data.size() <= 0) return nullptr;
    int size = data["tasks"].size();
    *s = size;
    Task* tasks = new Task[size];
     
    for (int i = 0; i < size; i++) {
        Time time; time.setTimeMls(data["tasks"][i]["time"].get<long>());
        tasks[i] = Task(
            data["tasks"][i]["id"].get<short>(),
            data["tasks"][i]["priority"].get<short>(),
            data["tasks"][i]["title"].get<string>(),
            data["tasks"][i]["description"].get<string>(),
            time
        );
    }
    return tasks;
}
 

int TaskService::getSizeArrayTask(std::string path)
{
    std::ifstream f(path);
    json data = json::parse(f);
    int size = data["tasks"].size();
    return size;
}

Task TaskService::loadTaskById(int id, std::string path)
{
    std::ifstream f(path);
    json data = json::parse(f);
    if (data.size() <= 0) return Task();// if file empty

    int size = data["tasks"].size();

    for (int i = 0; i < size; i++) {
        if (data["tasks"][i]["id"].get<short>() == id) {
           Time time; time.setTimeMls(data["tasks"][i]["time"].get<long>());
           return Task(
                data["tasks"][i]["id"].get<short>(),
                data["tasks"][i]["priority"].get<short>(),
                data["tasks"][i]["title"].get<string>(),
                data["tasks"][i]["description"].get<string>(),
                time
            );
        }
    }
    return Task();
}

bool TaskService::saveTask(Task& task, std::string path)
{
    std::ifstream f(path);
    json data = json::parse(f);
    if (data.size() <=0) {
        task.setId(1);
        data["tasks"][0] = setData(task); 
    }
    else{ 
        int size = data["tasks"].size() + 1;
        task.setId(size);
    // here you can set an order decending or ascending 
        data["tasks"][size-1] = this->setData(task); // add in tail
    }
    ofstream o(path);
    o << std::setw(8) << data << std::endl;
    return true;
}

bool TaskService::saveTasks(int size, Task* tasks, std::string path)
{
    json data;
    for (int i = 0; i < size; i++) {
        if (tasks[i].getId() < 100) { tasks[i].setId(i + 1); } // check if id is unique, if no set sequence
        /* 
            data["tasks"][i]["id"] = tasks[i].getId();
            data["tasks"][i]["priority"] = tasks[i].getPriority();
            data["tasks"][i]["title"] = tasks[i].getTitle();
            data["tasks"][i]["description"] = tasks[i].getDescription();
            data["tasks"][i]["time"] = tasks[i].getTimer()->getTimeMls();
        */
            data["tasks"][i] = setData(tasks[i]);
    }

    ofstream o(path);
    o << std::setw(8) << data << std::endl;
    return true;
}

bool TaskService::removeTask(short id, std::string path)
{
    std::ifstream f(path);
    json data = json::parse(f);
    if (data.size() <= 0) return false;// if file empty

    int size = data["tasks"].size();
    // check if id is present 
    bool idIsPresent = false;
    for (int i = 0; i < size; i++) {
        if (data["tasks"][i]["id"].get<short>() == id) {
            idIsPresent = true;
            break;
        }
    }
    if (!idIsPresent) return false;

    Task* tasks = new Task[size-1];
     for (int i = 0, j = 0; i < size - 1; i++) {
        if (data["tasks"][i]["id"].get<short>() == id) { j++; continue; }
        else  {
            Time time; time.setTimeMls(data["tasks"][i]["time"].get<long>());
            tasks[i-j] = //in array i-j return counter back at 'j' position
                Task(
                data["tasks"][i]["id"].get<short>(),
                data["tasks"][i]["priority"].get<short>(),
                data["tasks"][i]["title"].get<string>(),
                data["tasks"][i]["description"].get<string>(),
                time
            );
            
        }
    } 
    this->saveTasks(size-1, tasks, path);
    delete[] tasks;
    return true;
}

json TaskService::setData(Task& task)
{
    json data;
        data["id"] = task.getId();
        data["priority"] = task.getPriority();
        data["title"] = task.getTitle();
        data["description"] = task.getDescription();
        data["time"] = task.getTimer()->getTimeMls();

    return data;
}

 