#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Include.h"

#include "InputClass.h"
#include "GraphicsClass.h"

class SystemClass
{
public:
	bool Init();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MyWndProc(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR			m_appName;
	HINSTANCE		m_hInst;
	HWND			m_hWnd;
	InputClass*		m_Input;
	GraphicsClass*	m_Graphics;

public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* AppHandle = 0;