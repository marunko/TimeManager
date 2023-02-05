#include "MainWindow.h"


HWND newWin;
// constants sizes of list objs 
int width = 100;
int height = 50;

HWND createWindow(HWND hwind) {
	newWin = CreateWindowA("ComboBox", "NWindow", WS_CHILD | WS_VSCROLL | WS_VISIBLE, 1, 1, 500, 500, hwind, 0, 0, 0);
	//CreateWindowA("ListBox", "NWindow", WS_CHILD | WS_VSCROLL | WS_VISIBLE, 101, 101, 100, 100, hwind, 0, 0, 0);
	int x = 50;
	int y = 50;
	for (int i = 0, temp=1; i < 10; i++) {
		char a[] = "Item- ";
		a[5] = getNumber(i);
		 
		if (temp++ >3) {
			x += (width + 10);
			y = 50;
			temp =2;
		}
		CreateWindowA("Edit", a, WS_CHILD | WS_VISIBLE, x, y, width, height, newWin, 0, 0, 0);
		y += height + 10;
	}
	return newWin;
}
char getNumber(int n) {
	char ch[] = "0123456789";
	for (int i = 0; i < sizeof(ch) / sizeof(ch[0]); i++) {
		if (i == n) {
			return ch[i];
		}
	}
	return ch[0];
}
// 1. create WindowListItem class 
// 2. registerClasses method(); | 
// 3. create Button arrowStyle
// 4. Create WindowTimerClass andd register it (timers, clocks)
// 5.  launch timer 2d thread display
// 5.1 launch clock 2d thread display

// 6.  MainWindow arrangement Loop List of Windows 
// 6.0 create class Task
// 6.1 Parse file json to Task class array and set its data to WindowListItem

// 7. DialogWindow TaskCreateWindow
// 7.1 