#pragma once
#include <string>

// main class for inheritance by all windows
/// for comunication through Controller
using namespace std;
class WindowW
{
protected:
	string WStringToString(const wstring& wstr);
	wstring StringToWString(const string& str);
public:
	std::string virtual getName();
	void virtual update();
	void virtual updateItem();
};

