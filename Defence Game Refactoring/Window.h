#pragma once

#include "Include.h"

class Window
{
private:
	string ClassName;
	string WinName;
	HWND hWnd;
	HINSTANCE hInst;
	SIZE WinSize;
	int time_elapsed = 1000;

	VOID RegClass();
	BOOL MakeWindow();
	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

protected:
	virtual LRESULT MyWndProc(HWND, UINT, WPARAM, LPARAM);
	virtual VOID Render(HDC hdc);
	virtual VOID Update();

public:
	virtual ~Window() = default;

	bool NewWindow(HINSTANCE, int, int, LPCSTR);
	int MessageLoop();
	void SetTime(int flow);
	SIZE GetWinSize();
};