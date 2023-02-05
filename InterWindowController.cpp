#include "InterWindowController.h"

void InterWindowController::addWindowToList(std::string name, WindowW& window)
{
    this->windows[name] = &window;
}

WindowW* InterWindowController::getWindow(std::string str)
{
    return this->windows[str];
}

std::map<std::string, WindowW*> InterWindowController::getWindows()
{
    return this->windows;
}
 