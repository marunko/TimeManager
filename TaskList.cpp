#include "TaskList.h"
 

void TaskList::Display(HWND wind)
{
    int y = 10;
    // get Tasks TaskManager
	for (int i = 0; i < size; i++) {
   
        createTaskWindow(i, tasks[i], 10, y);
        y += 100;
	}
    this->updateTimeManager();

}

void TaskList::moveTaskWindows(int pos)
{
    for(int i = 0; i < this->size; i++)
        MoveWindow(this->tasks[i].getWindow(), 10, 
            (pos+taskWindowHeight*i)+20, taskWindowWidth, taskWindowHeight, TRUE);
}

void TaskList::updateTimeManager()
{
    long wt=0;
    for (int i = 0; i < size; i++) {
        wt+=tasks[i].getTimer()->getTimeMls();
    }
    timeManager->setWorking_Time(wt);
}

void TaskList::createTaskWindow(int i, Task &task, int x, int y)
{
    HWND* subwindows = new HWND[subWindowsSize];
    HWND parent = CreateWindowExA(0, "TaskList", "", WS_BORDER | WS_CHILD | WS_VISIBLE, x, y,
        taskWindowWidth, taskWindowHeight, main, 0, 0, 0);
    task.setWindow(parent);

    std::string s = std::to_string(i); // i

    subwindows[0] = CreateWindowExA(0, "static", s.c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE,
        20, 25, 20, 50,
        parent,
        NULL,
        0,
        NULL);
    
    std::string s2 = std::to_string(task.getPriority());
    subwindows[1] = CreateWindowExA(0, "static", s2.c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE,
        60, 25, 20, 50,
        parent,
        NULL,
        0,
        NULL); // from file
    // title
    subwindows[2] = CreateWindowExA(0, "static", task.getTitle().c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE,
        100, 25, 400, 50,
        parent,
        NULL,
        0,
        NULL);
    // time ? std::to_string(task.getTimer()->getTimeMls()).c_str()

    subwindows[3] = CreateWindowExA(0, "static", task.getTimer()->to_timeFormat().c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE,
        420, 25, 60, 50,
        parent,
        NULL,
        0,
        NULL);
    if(i ==0){
        if (!task.isCounting()) {
            subwindows[4] = CreateWindowExA(0, "button", "Start", WS_BORDER | WS_CHILD | WS_VISIBLE, 500, 25, 100, 50,
                parent, (HMENU)OnStart, 0, NULL); // OnPlay
        }
        else {
            subwindows[4] = CreateWindowExA(0, "button", "Stop", WS_BORDER | WS_CHILD | WS_VISIBLE, 500, 25, 100, 50,
                parent, (HMENU)OnPause, 0, NULL); // OnStop
        }
    }

    int t=1000+i;
    std::string s3 = "r-"+std::to_string(i);
    subwindows[5] = CreateWindowA("button", s3.c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE,
        610, 25, 100, 50, parent, (HMENU)t, 0, NULL);
    // or set directly createW by &&reference
    int up = t * 10; int down = up + 1;
    subwindows[5] = CreateWindowExA(0, "button", "U", WS_BORDER | WS_CHILD | WS_VISIBLE, 750, 10, 50, 38,
        parent, (HMENU)up, 0, NULL);

    subwindows[6] = CreateWindowExA(0, "button", "D", WS_BORDER | WS_CHILD | WS_VISIBLE, 750, 52, 50, 38,
        parent, (HMENU)down, 0, NULL);
    // set images to 
    task.setSubWindows(subwindows, 8);
    //delete[] subwindows;
}

WNDCLASS TaskList::NewWindow(HBRUSH BGcolor, HCURSOR cursor, HINSTANCE instance, HICON icon, LPCWSTR name, WNDPROC proc)
{
    WNDCLASS wnd = { 0 };

    wnd.hCursor = cursor;
    wnd.hIcon = icon;
    wnd.hbrBackground = BGcolor;
    wnd.hInstance = instance;
    wnd.lpszClassName = name;
    wnd.lpfnWndProc = proc;
    return wnd;
}

void TaskList::destroySubwindows(Task& task)
{

    for (int i = 0; i < subWindowsSize; i++) {
        
        DestroyWindow(task.getSubWindow(i));
    }
}

void TaskList::changePositionUp(int n)
{
    //thread t; //write file with new order
    int replaceN = 0;
    if (n == 0) {

        replaceN = size-1;
    }
    else {

        replaceN = n - 1; // prev task
    }
    Task t1 = tasks[n];
    tasks[n] = tasks[replaceN];
    tasks[replaceN] = t1;
    this->tmanager.saveAllTasksToday(this->size, tasks);
    this->update();
   
}

void TaskList::changePositionDown(int n)
{
    // need to rewrite all buttons, id, 
    int replaceN = 0;
    if (n == size-1) {
 
        replaceN = 0;
    }
    else {
      
        replaceN = n + 1; // prev task
    }
    Task t1 = tasks[n];
    tasks[n] = tasks[replaceN];
    tasks[replaceN] = t1;
    this->tmanager.saveAllTasksToday(this->size, tasks);
    this->update();
}

void TaskList::createList(HWND w)
{
    this->generalWindow = w;

    this->mainHeight = 500; 
    dynamicHeight = (taskWindowHeight * size) + (10 * size) + 20;
    scrollinfo.nMax = dynamicHeight; scrollinfo.nPos = 0;
    scroll=  CreateWindowExA(0, "General", "", WS_CHILD | WS_VISIBLE, 20, 280,
        900, this->mainHeight, generalWindow, 0, 0, 0);
    main = CreateWindowEx(0, L"static", L"",  WS_CHILD | WS_VISIBLE, 0, 0,
        900, this->dynamicHeight, scroll, 0, 0, 0);

    SetScrollInfo(scroll, SB_VERT, &this->scrollinfo, TRUE);
    this->Display(w);
}

void TaskList::removeTaskFromList(int n)
{
    // 1000 to size+1000
     // button code
    if (n >= size || n < 0) return;
   // MessageBoxA(generalWindow, std::to_string(n).c_str(), "destroying remove", MB_OK);
    this->destroySubwindows(tasks[n]);
    DestroyWindow(tasks[n].getWindow());
    // remove sub windows
    //tasks[n] = NULL;
   for (int i = n + 1; i < size; i++) {
        //MessageBoxA(generalWindow, std::to_string(i).c_str(), "destroying pos:", MB_OK);
        this->destroySubwindows(tasks[i]);
        DestroyWindow(tasks[i].getWindow());
        
        createTaskWindow(i-1, tasks[i], 10, (i-1)*100+10);
        //add argument Task(class)
   } 
    
    // resize
    this->size--;
    if (size == 0) {
        delete[] tasks; this->tasks = nullptr;
    }
    else{ 
        Task* newArr = new Task[size];
        for (int i = 0, j =0; i < size+1; i++) {
            if (i == n) { j++; continue; }
            newArr[i-j] = tasks[i]; //copy process! overload operator=
        }
        delete[] tasks;
        tasks = newArr;
    }
    this->updateTimeManager();
  
    // use controller to comunicate between window 
    // and cause immidiate update of TimeWindow
    // can use map<string, class>;
    if (n == 0) {
        KillTimer(this->generalWindow, Timer_TaskTime_ID);
        KillTimer(this->generalWindow, Display_Timer);
    }
    this->controller->getWindow("TimerWindow")->update();
    //this->update();
}

void TaskList::updateTaskList()
{
     
}
//--------------------------------------------------- update all
void TaskList::update()
{

    //1. remove all old windows and array
    for(int i =0; i < size; i++)
        removeTaskFromList((i)); // WARMING ! method is visual only, dont interfere in file from here
    //2. parse new data
    this->tasks = this->tmanager.getTasks(&this->size);
    //MessageBoxA(generalWindow, std::to_string(size).c_str(), "Size is", MB_OK);
    //3. create new windows
    if(this->size > 0){ 
        DestroyWindow(this->scroll);
        DestroyWindow(this->main);
        this->createList(this->generalWindow);
    }
     
   // this->Display(generalWindow);
   // MessageBoxA(generalWindow, std::to_string(size).c_str(), "Menu 2", MB_OK);
}
//--------------------------------------------- the same for one item update

void TaskList::OnScrollList(HWND w, WPARAM wp)
{
    this->scrollinfo.cbSize = sizeof(this->scrollinfo);
    GetScrollInfo(this->scroll, SB_VERT, &scrollinfo);
    switch (LOWORD(wp)) {
        case SB_LINEUP:
            //MessageBoxA(w,"UP", "W", 1);
            scrollinfo.nPos -= 25;
            break;
        case SB_LINEDOWN:
           // MessageBoxA(w, "SB_LINEDOWN", "S", 1);
            scrollinfo.nPos += 25;
            break;
        case SB_THUMBTRACK:
            scrollinfo.nPos = HIWORD(wp);
        default:
            break;
     }
    SetScrollInfo(this->scroll, SB_VERT, &scrollinfo, TRUE);
   // MessageBoxA(w, std::to_string(scrollinfo.nPos).c_str(), "S", 1);
    //this->moveTaskWindows(-scrollinfo.nPos);
    MoveWindow(this->main, 0, -scrollinfo.nPos, 900, this->dynamicHeight, TRUE);
    return;
}

void TaskList::OnRemoveClick(HWND w, WPARAM wp)
{
    // starts from 1000
    for (int i = 0; i < size; i++) {
        if (wp == (i + 1000)) {
            int tempSize = this->size;
            this->tmanager.removeTaskToday((i)+1);
            if (double((size) / ((this->dynamicHeight - 20 - (10 * tempSize)) / 100)) > 0.5 ||
                this->size ==0)
                this->removeTaskFromList(i);
            else
            {
              //  MessageBoxA(w, std::to_string(size).c_str(), "Size is", MB_OK);
                this->update();
            }
            //this->tmanager.removeTaskToday((i)+1);
           // MessageBoxA(w, std::to_string(size).c_str(), "Menu 2", MB_OK);

            return;
        }
    }
}
void TaskList::OnStartClick(HWND w, WPARAM wp)
{
    if (wp == OnStart) {
        
        HWND startWindow = tasks[0].getSubWindow(4);
        DestroyWindow(startWindow);
        startWindow = CreateWindowExA(0, "button", "Stop", WS_BORDER | WS_CHILD | WS_VISIBLE, 500, 25, 100, 50,
        tasks[0].getWindow(), (HMENU)OnPause, 0, NULL); // OnStop
        tasks[0].setCounting(true);
        // start counting time
        tasks[0].setSubWindow(startWindow, 4);
        //startTimer();
       /// threadWT = new thread(&TaskList::counting, this);

        SetTimer(this->generalWindow,             // handle to main window 
            Timer_TaskTime_ID,    // timer identifier 
            500,                 // 1-second interval 
            (TIMERPROC)TaskProc);
        SetTimer(this->generalWindow,             // handle to main window 
            Display_Timer,    // timer identifier 
            500,                 // 1-second interval 
            (TIMERPROC)TaskProc);

    }
}
void TaskList::OnPauseClick(HWND w, WPARAM wp)
{
    if (wp == OnPause) {
        HWND stopWindow = tasks[0].getSubWindow(4);
        DestroyWindow(stopWindow);
        stopWindow = CreateWindowExA(0, "button", "Start", WS_BORDER | WS_CHILD | WS_VISIBLE, 500, 25, 100, 50,
            tasks[0].getWindow(), (HMENU)OnStart, 0, NULL); // OnStop
        tasks[0].setCounting(false);
        // start counting time
        tasks[0].setSubWindow(stopWindow, 4);
        // stop timer
       // delete threadWT;
        KillTimer(this->generalWindow, Timer_TaskTime_ID);
        KillTimer(this->generalWindow, Display_Timer);
         
    }
}
 

void TaskList::registerClasses(HINSTANCE instance)
{
    WNDCLASS wndclass = NewWindow((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_HAND), instance,
        0,L"General", TaskProc);
    WNDCLASS subClass = NewWindow((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_HAND), instance,
        0, L"TaskList", TaskProc);
    RegisterClassW(&wndclass);
    RegisterClassW(&subClass);
    
}

void TaskList::OnChangeOrderClick(HWND w, WPARAM wp)
{
    for (int i = 0; i < size; i++) {
        int t = (i + 1000) * 10;
        if (wp == t) {
            //MessageBoxA(this->generalWindow, "U", to_string(t).c_str(), MB_OK);
            this->OnPauseClick(w, OnPause);
            this->changePositionUp(i);
            return;
        }
        else if ((t+1)== wp) {
            //MessageBoxA(this->generalWindow, "D", std::to_string(t+1).c_str(), MB_OK);
            this->OnPauseClick(w, OnPause);
            this->changePositionDown(i);
            return;
        }
    }
}
 

void TaskList::counting()
{
  
    long t = tasks[0].getTimer()->getTimeMls() - 500;
    tasks[0].getTimer()->setTimeMls(t);
    if (tasks[0].getTimer()->getTimeMls()<0) {
        // inform user time is out 
        // signal mp3
        MessageBoxA(this->generalWindow, "Message", "Time Out", 0);
        this->removeTaskFromList(0);
        this->tmanager.removeTaskToday(1);
    } /*
    while (tasks[0].isCounting()) {

        long t = tasks[0].getTimer()->getTimeMls() - 500;
        tasks[0].getTimer()->setTimeMls(t);
        this->timeManager->countingDownDaily_Activity(); // -500
        if (tasks[0].getTimer()->getTimeMls() < 0) {
            // inform user time is out 
            this->removeTaskFromList(0);
            this->tmanager.removeTaskToday(1);
        }
        this_thread::sleep_for(chrono::microseconds(500));
     } */
}
void TaskList::saveTaskCounterOnExit()
{
    tmanager.removeTaskToday(0);
    tmanager.saveNewTaskToday(tasks[0]);
}


void TaskList::DisplayCounter()
{
    std::wstring s = tasks[0].getTimer()->to_timeFormatW();
    SetWindowText(tasks[0].getSubWindow(3), (LPCWSTR)s.c_str());
}

thread* TaskList::getThread()
{
    return this->threadWT;
}

TaskList::TaskList(TimeManager& timeManager, InterWindowController &c)
{
     
	// parse file and set size 
	//size = 5; // set size from file
   // this->size = this->tmanager.getSize();
    int i = 0; subWindowsSize = 8;
    tasks = this->tmanager.getTasks(&this->size);
    taskWindowHeight = 100;
    taskWindowWidth = 800;
    this->timeManager = &timeManager;
    this->controller = &c;
    this->controller->addWindowToList("TaskList", *this);
    
    scrollinfo.cbSize = sizeof(scrollinfo); scrollinfo.nPos = 0;
    scrollinfo.nMax = 800; scrollinfo.nPage = 400; scrollinfo.fMask = SIF_ALL;
    scrollinfo.nMin = 0;
     
}
 

TaskList::~TaskList()
{
	delete[] tasks;
}
