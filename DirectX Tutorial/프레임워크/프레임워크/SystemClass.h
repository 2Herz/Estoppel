#pragma once

class InputClass;
class GraphicsClass;

class SystemClass
{
private:
	Text m_WinName;
	INST m_hInst;
	HWND m_hWnd;

	InputClass* m_Input = nullptr;
	GraphicsClass* m_Graphics = nullptr;

public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MyWndProc(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* ApplicationHandle = 0;