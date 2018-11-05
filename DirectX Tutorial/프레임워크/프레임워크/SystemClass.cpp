#include "stdafx.h"
#include "SystemClass.h"
#include "InputClass.h"
#include "GraphicsClass.h"

SystemClass::SystemClass()
{
}

SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	//	윈도우 창 가로, 세로 넓이 변수 초기화
	int screenWidth = 0;
	int screenHeight = 0;

	//	윈도우 생성 초기화
	InitializeWindows(screenWidth, screenHeight);

	//	m_Input 객체 생성. 이 클래스는 추후 사용자의 키보드 입력 처리에 사용됩니다.
	m_Input = new InputClass;

	if (!m_Input)
	{
		return false;
	}

	//	m_Input 객체 초기화
	m_Input->Initialize();

	//	m_Graphics 객체 생성. 그래픽 랜더링을 처리하기 위한 객체입니다.
	m_Graphics = new GraphicsClass;

	if (!m_Graphics)
	{
		return false;
	}

	//	m_Graphics 객체 초기화
	return m_Graphics->Initialize(screenWidth, screenHeight, m_hWnd);

}

void SystemClass::Shutdown()
{
}

void SystemClass::Run()
{
}

LRESULT SystemClass::MyWndProc(HWND, UINT, WPARAM, LPARAM)
{
	return LRESULT();
}

bool SystemClass::Frame()
{
	return false;
}

void SystemClass::InitializeWindows(int &, int &)
{
}

void SystemClass::ShutdownWindows()
{
}
