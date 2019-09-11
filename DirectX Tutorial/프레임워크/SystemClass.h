#pragma once

#define WIN32_LEAN_AND_MEAN

//	기본헤더파일
#include "Include.h"

//	사용자 정의 헤더파일
#include "InputClass.h"
#include "GraphicsClass.h"

/*
	이 곳은 시스템 클래스이다.

	시스템 클래스는 전체 사이클을 관리하고

	기본윈도우 위에 DirectX 11 을 띄우기 위한 클래스이다.

	이 클래스에서는

	기본 윈도우 창을 띄우고

	Frame 함수를 통해 DirectX 창을 랜더하고 모니터로 출력한다.

	시스템 클래스는 입력과 그래픽 클래스를 자식으로 가지고 관리한다.
*/
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