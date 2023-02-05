// WindowsTests.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsTests.h"
#include "MainWindow.h"
#include "ExtraTestWindow.h"
#include "TaskList.h"
#include "TimeManager.h"
#include "TimerWindow.h"
#include "ThreeButtonsWindow.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hWnd; // general window

InterWindowController contrl;
TimeManager timeManager; // one for all, save to taskList 

TaskList taskList = { timeManager,contrl };       // global task list
TimerWindow timeWindow = { timeManager, contrl };
ThreeButtonsWindow threeButtonsWindow = {contrl, timeManager };
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
 
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    // TODO: Разместите код здесь.
 
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSTESTS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    taskList.registerClasses(hInstance);
    timeWindow.setData((TIMERPROC)TaskProc);
    threeButtonsWindow.setProcess((INT_PTR)ThreeButtonsProc);
    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    // After instance initialization you can start use Dialog Windows here 
    threeButtonsWindow.setInstance(hInstance);
     
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSTESTS));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            if (msg.message == WM_TIMER)
            {
                msg.hwnd = hWnd;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
     
    timeWindow.liquidateActivityThread();
    timeWindow.getThread()->join();
    
    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSTESTS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSTESTS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
   //standard width/height CW_USEDEFAULT, 0
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1000, 900, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        //createWindow(hWnd);
        //createSubWindow(hWnd);
        timeManager.OnAppStart();
        taskList.createList(hWnd);
        timeWindow.CreateTimeWindow(hWnd);
        threeButtonsWindow.CreateThreeButtonsWindow(hWnd); // ? ref
        break;
    case WM_COMMAND:
        {     
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
           // if (wmId > 1000 && wmId < 1100) { taskList.OnRemoveClick(hWnd, wParam); break; }
            switch (wmId)
            {
            case OnClick:

                MessageBoxA(hWnd, "Menu 2 Clicked", "Menu 2", MB_OK);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                // stop counter
                DestroyWindow(hWnd);
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        // Dont forget to save current tasks and its timing to file 
        // check time where to save todayFile or tomorrow 
        taskList.saveTaskCounterOnExit();
        timeManager.OnAppDestroy();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
LRESULT CALLBACK TaskProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {

    case WM_COMMAND:
        threeButtonsWindow.OnButtonCommand(hWnd, wParam);
        taskList.OnStartClick(hWnd, wParam);
        taskList.OnPauseClick(hWnd, wParam);
        if (wParam > 1000 && wParam < 1200) {
            //MessageBoxA(hWnd, std::to_string(wParam).c_str(), "Menu 2", MB_OK);
            taskList.OnRemoveClick(hWnd, wParam);
            break;
        }
        if (wParam >= 10000 && wParam < 12000) {
            //MessageBoxA(hWnd, std::to_string(wParam).c_str(), "Menu 2", MB_OK);
            taskList.OnChangeOrderClick(hWnd, wParam);
            break;
        }
        return 0;
    case WM_VSCROLL:
        taskList.OnScrollList(hWnd, wParam);
        break;
    case WM_TIMER:
        
        switch (LOWORD(wParam)) {
            // count down TaskTime and WorkTime 1 sec
            case Timer_TaskTime_ID:
                timeManager.countingDown();
                taskList.counting();                 
                break;
            // Redisplay one in 500mls 
            case Display_Timer:
                
                taskList.DisplayCounter();
                timeWindow.TimerRun();
                break;
            // clock & Activity
            case Timer_OneSec_Endless:
                //timeManager.countingDownDaily_Activity();
                break;
            case Timer_Clock_ID:
                // clock & Activity
                timeWindow.DailyRun();
                timeWindow.ClockRun();
                break;
            case Timer_On_Activity:
                timeManager.isOutOfActivityTime(hWnd);
        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
INT_PTR CALLBACK ThreeButtonsProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        threeButtonsWindow.OnAboutCreate(hDlg, wParam);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        threeButtonsWindow.OnAboutCommand(hDlg, wParam);
        break;
    }
    return (INT_PTR)FALSE;
}