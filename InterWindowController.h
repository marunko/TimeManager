#pragma once
#include <map>
#include "WindowW.h"
#include <string>
class InterWindowController
{

	std::map<std::string, WindowW*> windows;
public:
	void addWindowToList(std::string, WindowW&);

	WindowW* getWindow(std::string);
	std::map<std::string, WindowW*> getWindows();



};

