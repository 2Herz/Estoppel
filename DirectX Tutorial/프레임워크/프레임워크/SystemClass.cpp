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
	//	������ â ����, ���� ���� ���� �ʱ�ȭ
	int screenWidth = 0;
	int screenHeight = 0;

	//	������ ���� �ʱ�ȭ
	InitializeWindows(screenWidth, screenHeight);

	//	m_Input ��ü ����. �� Ŭ������ ���� ������� Ű���� �Է� ó���� ���˴ϴ�.
	m_Input = new InputClass;

	if (!m_Input)
	{
		return false;
	}

	//	m_Input ��ü �ʱ�ȭ
	m_Input->Initialize();

	//	m_Graphics ��ü ����. �׷��� �������� ó���ϱ� ���� ��ü�Դϴ�.
	m_Graphics = new GraphicsClass;

	if (!m_Graphics)
	{
		return false;
	}

	//	m_Graphics ��ü �ʱ�ȭ
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
