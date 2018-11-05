#pragma once

#include <Windows.h>

class InputClass;
class Graphics;

class System
{
public:
	System();
	System(const System&);
	~System();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MyWndProc(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_AppName;
	HINSTANCE m_hInst;
	HWND m_hWnd;

	InputClass* m_Input = nullptr;
	Graphics* m_Graphics = nullptr;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static System* AppHandle = 0;