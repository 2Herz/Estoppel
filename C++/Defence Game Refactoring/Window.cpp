#include "Window.h"

Window *mainWindow = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return mainWindow->MyWndProc(hWnd, message, wParam, lParam);
}

VOID Window::RegClass()
{
	WNDCLASS mywnd = {};

	mywnd.lpszClassName = ClassName.c_str();
	mywnd.hInstance = hInst;
	mywnd.lpfnWndProc = WndProc;
	mywnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	mywnd.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	mywnd.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClass(&mywnd);
}

BOOL Window::MakeWindow()
{
	mainWindow = this;

	RECT rt = { 0, 0, WinSize.cx, WinSize.cy };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindow(ClassName.c_str(), WinName.c_str(), WS_OVERLAPPEDWINDOW, 455, 0, rt.right - rt.left, rt.bottom - rt.top, nullptr, nullptr, hInst, nullptr);

	if (hWnd == nullptr)
	{
		mainWindow = nullptr;
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);
	
	return TRUE;
}

LRESULT Window::MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_TIMER:
		{
			Update();
			InvalidateRect(hWnd, nullptr, TRUE);
		}break;
	}
}