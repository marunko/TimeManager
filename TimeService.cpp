#include "TimeService.h"

using namespace std;
using json = nlohmann::json;
 
TimeService::TimeService(std::string path)
{
    this->path = path;
}

void TimeService::saveDate(TimeOut& t)
{
    // save close time 
    json data;
    data["time"]["date"] = t.date;  
    data["time"]["activityTLeft"] = t.activityTLeft;// mls/1000
    // act time starts from first computer launch
    // set dead zone till which AT may be counted 3am-6am
    // if first launch in dead zone - recalculate 6am + 16h
    ofstream o(path);
    o << std::setw(8) << data << std::endl;
}

TimeOut TimeService::loadsavedDate()
{
    std::ifstream f(path);
    json data = json::parse(f);
    TimeOut t = {
        data["time"]["date"].get<long>(), 
        data["time"]["activityTLeft"].get<long>()
    };
    return t;
}
