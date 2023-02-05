#include "ThreeButtonsWindow.h"
#include "TaskManager.h"
#include "WeekListWindow.h"
 
ThreeButtonsWindow::ThreeButtonsWindow(InterWindowController& iwc, TimeManager& tm)
{
	controller = &iwc;
	timeManager = &tm;
}

void ThreeButtonsWindow::CreateThreeButtonsWindow(HWND& w)
{
	parentGeneral = w;
	thisButtonsWindow = CreateWindowExA(1, "General", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 20, 230,
		900, 50, parentGeneral, 0, 0, 0);

	 
	CreateWindowExA(1, "button", "Weekly List", WS_BORDER | WS_CHILD | WS_VISIBLE, margin_left, margin_top,
		bwidth, bheight, thisButtonsWindow, (HMENU)Weekly_task_button, 0, 0);
 
	CreateWindowExA(1, "button", "Tomorrow", WS_BORDER | WS_CHILD | WS_VISIBLE, (margin_left*2+bwidth), margin_top,
		bwidth, bheight, thisButtonsWindow, (HMENU)Tomorrow_task_button, 0, 0);
	CreateWindowExA(1, "button", "Add New Task", WS_BORDER | WS_CHILD | WS_VISIBLE, ((margin_left*3)+ (bwidth*2)), margin_top,
		bwidth, bheight, thisButtonsWindow, (HMENU)Add_task_button, 0, 0);
}

void ThreeButtonsWindow::OnButtonCommand(HWND& w, WPARAM wp)
{
	 
	switch (wp) {

		case Weekly_task_button:
			//MessageBoxA(w, "Menu 2 Clicked", "Menu 1", MB_OK);
			 
			  week.createList(w);

			break;
		case Tomorrow_task_button:
			//MessageBoxA(w, "Menu 2 Clicked", "Menu 2", MB_OK);
			CreateWindowW(L"General", L"", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100,100, 300, 500,
				parentGeneral, 0,0,0);
			break;
		case Add_task_button:
			DialogBox(this->hinstance, MAKEINTRESOURCE(IDD_ADDTASKBOX), w,  (DLGPROC)this->proc);
			break;
		default:
			break;
	}
}

void ThreeButtonsWindow::setInstance(HINSTANCE& h)
{
	this->hinstance = h;
}

void ThreeButtonsWindow::setProcess(INT_PTR pr)
{
	this->proc = pr;
}

void ThreeButtonsWindow::OnAboutCommand(HWND& w, WPARAM wp)
{
	if (LOWORD(wp) == IDOK || LOWORD(wp) == IDCANCEL)
	{
		//CHAR text[255] = { 0 };
		 
		TCHAR hour[2], minutes[2];
		TCHAR title[100], description[200];
		GetDlgItemText(w, IDC_EDIT_TITLE, title, 100);
		GetDlgItemText(w, IDC_EDIT_DESC, description, 200);
		GetDlgItemText(w, IDC_EDIT_HOUR, hour, 2);
		GetDlgItemText(w, IDC_EDIT_MINUTES, minutes, 2);
	 
		TaskManager tmanager;  

		//long t = 5000; // verify and parse time 
		Time time = this->timeManager->timeParseFromString(this->WStringToString(hour), 
			this->WStringToString(minutes));
		Task task = {0,3, this->WStringToString(title), this->WStringToString(description), time};
		bool flag = tmanager.saveNewTaskToday(task);
		this->controller->getWindow("TaskList")->update();
		this->controller->getWindow("TimerWindow")->update();

		/* 
		if (tmanager.isWorkingTimeAvailable(this->timeManager->getMAX_Working_Time(), *task.getTimer())) {
			tmanager.saveNewTaskToday(task);
		}
		else if (tmanager.isTomorrowAvailable(*task.getTimer())) {
			//tmanager.saveNewTaskTomorrow(task);
		}
		else if(tmanager.isWeekFree()){
			//tmanager.saveNewTaskWeek(task);
		}*/
		// logic

		if (!flag) MessageBoxA(w, "NOT Saved", "Repeate", MB_OK);
		EndDialog(w, LOWORD(wp));

		return;
	}
	// other commands
	switch (LOWORD(wp))
	{
	
	default:
		break;
	}
}

void ThreeButtonsWindow::OnAboutCreate(HWND& w, WPARAM wp)
{
	//SetDlgItemTextW(w, IDC_EDIT_DESC, L"add description here...");
	//SetDlgItemTextW(w, IDC_EDIT_HOUR, L"00");
	//SetDlgItemTextW(w, IDC_EDIT_MINUTES, L"00");
}
 
 