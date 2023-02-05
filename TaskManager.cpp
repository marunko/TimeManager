#include "TaskManager.h"

Task* TaskManager::getTasks(int *size)
{
    return this->service.loadTasks(size, pathToday);
}
// By stack
Task* TaskManager::getTasksToday(int* size)
{
    return this->service.loadTasks(size, pathToday);
}
Task* TaskManager::getTasksTomorrow(int* size)
{
    return this->service.loadTasks(size, pathTomorrow);
}
Task* TaskManager::getTasksWeek(int* size)
{
    return this->service.loadTasks(size, pathWeek);
}

int TaskManager::getSize()
{
    return this->service.getSizeArrayTask(pathToday);
}

Task TaskManager::getATaskById(int id)
{
    return this->service.loadTaskById(id, pathToday);
}
//checkers 
bool TaskManager::isWorkingTimeAvailable(Time Wtime, Time& taskTime)
{
    int size = 0;
    Task *tasks = this->service.loadTasks(&size, pathToday);
    long long generalTime=0;
    for (int i = 0; i < size; i++) {
        generalTime += tasks[i].getTimer()->getTimeMls();
    }
    generalTime += taskTime.getTimeMls();
    if (generalTime > Wtime.getTimeMls()) { delete[] tasks; return false; }
    delete[] tasks;
    return true;

}
bool TaskManager::isTomorrowAvailable(Time& taskTime) {
    Time workingTime = {8*3600000};// set 8 hours
    return this->isWorkingTimeAvailable(workingTime, taskTime);
}
bool TaskManager::isWeekFree() {
    return this->service.getSizeArrayTask(pathWeek) < 40 ? true : false;
}

Task TaskManager::getATaskTodayById(int id)
{
    return this->service.loadTaskById(id, pathToday);
}
Task TaskManager::getATaskTomorrowById(int id)
{
    return this->service.loadTaskById(id, pathTomorrow);
}
Task TaskManager::getATaskWeekById(int id)
{
    return this->service.loadTaskById(id, pathWeek);
}

bool TaskManager::saveAllTasksToday(int size, Task *task) {

    return this->service.saveTasks(size,task, pathToday);
}

bool TaskManager::saveNewTaskToday(Task& task) {

    return this->service.saveTask(task, pathToday);
}
bool TaskManager::saveNewTaskTomorrow(Task& task) {
    return this->service.saveTask(task, pathTomorrow);
}
bool TaskManager::saveNewTaskWeek(Task& task) {
    return this->service.saveTask(task, pathWeek);
}

bool TaskManager::removeTaskToday(short id) {
     
    return this->service.removeTask(id, pathToday);
}