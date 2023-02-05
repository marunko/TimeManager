#include "ExtraTestWindow.h"



HWND createSubWindow(HWND w) {
 // RoW Window
    HWND wind = CreateWindowExA(0, "static", "", WS_BORDER | WS_CHILD | WS_VISIBLE,
        20, 50, 800, 100,
        w,
        NULL,
        0,
        NULL);
    // may set also a number
    // HWND rowNumber = ;
    CreateWindowExA(0, "static", "#", WS_BORDER | WS_CHILD | WS_VISIBLE,
        20, 25, 20, 50,
        wind,
        NULL,
        0,
        NULL); 
    std::string s = "!!!";
    CreateWindowExA(0, "static", s.c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE,
        60, 25, 20, 50,
        wind,
        NULL,
        0,
        NULL); // from file
    
    CreateWindowExA(0, "static", "Task Text Here from file", WS_BORDER | WS_CHILD | WS_VISIBLE,
        100, 25, 400, 50,
        wind,
        NULL,
        0,
        NULL);
    CreateWindowExA(0, "button", "pause", WS_BORDER | WS_CHILD | WS_VISIBLE,
        500, 25, 100, 50,
        wind,
        NULL,
        0,
        NULL);
    CreateWindowExA(0, "button", "remove", WS_BORDER | WS_CHILD | WS_VISIBLE,
        610, 25, 100, 50,
        wind,
        NULL,
        0,
        NULL);
    return wind;
}

HWND createTimerWindow(HWND w) {
    
    return w;
}