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
	//	m_Graphics ��ü ��ȯ
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Input;
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

void SystemClass::Run()
{
	//	�޽��� ����ü ���� �� �ʱ�ȭ
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//	����ڷκ��� ���� �޽����� ���������� �޽��� ������ ���ϴ�.
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			//	���� �޽����� ���� ��� �޽��� ������ Ż���մϴ�.
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//	�� �ܿ��� Frame �Լ��� ó���մϴ�.
			if (!Frame()) break;
		}
	}
}

bool SystemClass::Frame()
{
	//	ESC Ű ���� �� ���� ���θ� ó���մϴ�.
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	//	�׷��� ��ü�� Frame�� ó���մϴ�.
	return m_Graphics->Frame();
}

LRESULT SystemClass::MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	Ű���尡 �������°� ó��
		case WM_KEYDOWN:
		{
			//	Ű ���� flag�� m_Input ��ü�� ó���ϵ��� �մϴ�.
			m_Input->KeyDown((unsigned int)wParam);
			return 0;
		}

		//	Ű���尡 �������°� ó��
		case WM_KEYUP:
		{
			//	Ű ���� flag�� m_Input ��ü�� ó���ϵ��� �մϴ�.
			m_Input->KeyUp((unsigned int)wParam);
			return 0;
		}

		//	�� ���� ��� �޽������� �⺻ �޽��� ó���� �ѱ�ϴ�.
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	//	�ܺ� �����͸� �� ��ü�� �����մϴ�.
	ApplicationHandle = this;

	//	�� ���α׷��� �ν��Ͻ��� �����ɴϴ�.
	m_hInst = GetModuleHandle(nullptr);

	//	���α׷� �̸��� �����մϴ�.
	m_WinName = L"DX11 FrameWork";

	//	windows Ŭ������ �Ʒ��� ���� �����մϴ�.
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
	wc.lpszClassName = nullptr;
	wc.lpszClassName = m_WinName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//	windows class�� ����մϴ�.
	RegisterClassEx(&wc);

	//	����� ȭ���� �ػ󵵸� �о�ɴϴ�.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int posX = 0;
	int posY = 0;

	//	FULL_SCREEN ���� ���� ���� ȭ���� �����մϴ�.
	if (FULL_SCREEN)
	{
		//	Ǯ��ũ�� ���� �����ߴٸ� ����� ȭ�� �ػ󵵸� �׽�ũ�� �ػ󵵷� �����ϰ� ������ 32bit�� �����մϴ�.
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPanningWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPanningHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//	Ǯ��ũ������ ���÷��� ������ �����մϴ�.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		//	������ ����� ��� 800 * 600 ũ�⸦ �����մϴ�.
		screenWidth = 800;
		screenHeight = 600;

		//	������ â�� ����, ������ �� ��� ������ �մϴ�.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//	�����츦 �����ϰ� �ڵ��� ���մϴ�.
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_WinName, m_WinName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, posX, posY, screenWidth, screenHeight, nullptr, nullptr, m_hInst, nullptr);

	//	�����츦 ȭ�鿡 ǥ���ϰ� ��Ŀ���� �����մϴ�.
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
}

void SystemClass::ShutdownWindows()
{
	//	Ǯ��ũ�� ��忴�ٸ� ���÷��� ������ �ʱ�ȭ�մϴ�.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(nullptr, 0);
	}

	//	â�� �����մϴ�.
	DestroyWindow(m_hWnd);
	m_hWnd = nullptr;

	//	���α׷� �ν��Ͻ��� �����մϴ�.
	UnregisterClass(m_WinName, m_hInst);

	//	�ܺ������� ������ �ʱ�ȭ�մϴ�.
	m_WinName = nullptr;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	������ ���Ḧ Ȯ���մϴ�.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		//	�����찡 �������� Ȯ���մϴ�.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		//	�� ���� ��� �޽������� �ý��� Ŭ������ �޽��� ó���� �ѱ�ϴ�.
		default:
		{
			return ApplicationHandle->MyWndProc(hWnd, message, wParam, lParam);
		}
	}
}
