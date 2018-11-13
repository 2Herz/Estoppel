#pragma once

class Input;
class Graphics;

class System
{
private:
	LPCWSTR m_WinName;
	HINSTANCE m_hInst;
	HWND m_hWnd;

	Input* m_Input = nullptr;
	Graphics* m_Graphics = nullptr;

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

public:
	System();
	System(const System&);
	~System();

public:
	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MyWndProc(HWND, UINT, WPARAM, LPARAM);
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static System* Handle = 0;