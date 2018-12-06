#include "stdafx.h"
#include "System.h"
#include "Input.h"
#include "Graphics.h"

System::System()
{
}

System::System(const System& other)
{
}

System::~System()
{
}

bool System::Initialize()
{
	//	������ â ����, ���� ���� ���� �ʱ�ȭ
	int screenWidth = 0;
	int screenHeight = 0;

	//	������ ���� �ʱ�ȭ
	InitializeWindows(screenWidth, screenHeight);

	//	m_Input ��ü ����. �� Ŭ������ ���� ������� Ű���� �Է� ó���� ����
	m_Input = new Input;
	if (!m_Input)
	{
		return false;
	}

	//	m_Input ��ü �ʱ�ȭ
	m_Input->Initialize();

	//	m_Graphics ��ü ����. �׷��� �������� ó���ϱ� ���� ��ü��
	m_Graphics = new Graphics;
	if (!m_Graphics)
	{
		return false;
	}

	//	m_Graphics ��ü �ʱ�ȭ.
	return m_Graphics->Initialize(screenWidth, screenHeight, m_hWnd);
}

void System::Shutdown()
{
	//	m_Graphics ��ü ��ȯ
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	//	m_Input ��ü ��ȯ
	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	//	Window ���� ó��
	ShutdownWindows();
}

void System::Run()
{
	//	�޽��� ����ü ���� �� �ʱ�ȭ
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//	����ڷκ��� ���� �޽����� ���������� �޽��������� ��
	while (true)
	{
		//	������ �޽��� ó��
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			//	���� �޽����� ���� ��� �޽��� ���� Ż��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//	�� ���� ��쿡�� Frame() �Լ��� ����
			if (!Frame()) break;
		}
	}
}

bool System::Frame()
{
	//	ESC Ű ���� �� ���� ���� ó��
	if (m_Input->IsKeyDown(VK_ESCAPE)) return false;

	//	�׷��� ��ü�� Frame() �Լ��� ����
	return m_Graphics->Frame();
}

LRESULT CALLBACK System::MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	Ű �Է� ���� ó��
		//	������ ��
	case WM_KEYDOWN:
	{
		//	Ű�� ������ �� m_Input ��ü�� ó��
		m_Input->KeyDown((unsigned int)wParam);
		return 0;
	}
	//	Ű�� ���� ��
	case WM_KEYUP:
	{
		//	Ű�� ������ �� m_Input ��ü�� ó��
		m_Input->KeyUp((unsigned int)wParam);
		return 0;
	}
	//	�� �� ��� �޽��� ó���� �⺻ �޽��� ó���� �ѱ�
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
}

void System::InitializeWindows(int& screenWidth, int& screenHeight)
{
	//	�ܺ� �����͸� �� ��ü�� ����
	Handle = this;

	//	�ν��Ͻ��� ���´�.
	m_hInst = GetModuleHandle(nullptr);

	//	���α׷��� �̸��� ����
	m_WinName = L"Direct X �ʱ�ȭ";

	//	Window Class ����
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInst;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_WinName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//	Window Class ���
	RegisterClassEx(&wc);

	//	����� �ػ� ������
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int posX = 0;
	int posY = 0;

	//	FULL_SCREEN ���� ���� ���� ȭ�鼳��
	if (FULL_SCREEN)
	{
		//	�ִ�ȭ�� ������ �� ����� ȭ�� �ػ󵵸� ����ũž �ػ󵵷� �����ϰ� ������ 32bit�� ����
		DEVMODE ScreenSetting;
		memset(&ScreenSetting, 0, sizeof(ScreenSetting));
		ScreenSetting.dmSize = sizeof(ScreenSetting);
		ScreenSetting.dmPelsWidth = (unsigned long)screenWidth;
		ScreenSetting.dmPelsHeight = (unsigned long)screenHeight;
		ScreenSetting.dmBitsPerPel = 32;
		ScreenSetting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//	�ִ�ȭ������ ����
		ChangeDisplaySettings(&ScreenSetting, CDS_FULLSCREEN);
	}
	else
	{
		//	������ ����� ��� 800, 600 ũ��� ����
		screenWidth = 800;
		screenHeight = 600;

		//	������ â�� ����, ������ �� ��� ������ ����
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//	������ â ����
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_WinName, m_WinName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, nullptr, nullptr, m_hInst, nullptr);

	//	���� ������ ������ â�� ȭ�鿡 ����ϰ� ��Ŀ�� ����
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
}

void System::ShutdownWindows()
{
	//	�ִ�ȭ�� ���¿��ٸ� ���÷��� ���� �ʱ�ȭ
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(nullptr, 0);
	}

	//	������ â ����
	DestroyWindow(m_hWnd);
	m_hWnd = nullptr;

	//	�ν��Ͻ� ����
	UnregisterClass(m_WinName, m_hInst);
	m_hInst = nullptr;

	//	�ܺ� ������ �ʱ�ȭ(�����찴ü�ʱ�ȭ)
	//	������ ��ü�� �� �����ͷ� �����߱� ������...
	Handle = nullptr;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	������ ���� Ȯ��
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	//	�����찡 �������� Ȯ��
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	//	�� ���� ��� �޽����� �ý��� Ŭ������ �޽��� ó���� �ѱ�
	default:
	{
		return Handle->MyWndProc(hWnd, message, wParam, lParam);
	}
	}
}