#include "SystemClass.h"

SystemClass::SystemClass() : m_Input(nullptr), m_Graphics(nullptr)
{
}

SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Init()
{
	//	�Լ��� ���ڷ� �ѱ������ ������, ������ ���� �� ���� ���� �ʱ�ȭ
	int screenWidth = 0;
	int screenHeight = 0;
	bool result = false;

	//	������ API �ʱ�ȭ
	InitWindows(screenWidth, screenHeight);

	//	�Է� ��ü ����-> �� ��ü�� ������� Ű���� �Է��� ��� ó���� ���
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	//	�Է� ��ü �ʱ�ȭ
	m_Input->Init();

	//	�׷��� ��ü ����-> �� ��ü�� �� ���α׷��� ��� �׷��� ������ ó���� ���
	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}

	//	�׷��� ��ü �ʱ�ȭ
	result = m_Graphics->Init(screenWidth, screenHeight, m_hWnd);
	if (!result)
	{
		return false;
	}

	return true;
}

void SystemClass::Shutdown()
{
	//	�׷��� ��ü �޸� ����
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = nullptr;
	}

	//	�Է� ��ü �޸� ����
	if (m_Input)
	{
		delete m_Input;
		m_Input = nullptr;
	}

	//	������ ����
	ShutdownWindows();
}

void SystemClass::Run()
{
	MSG msg;
	bool done = false;
	bool result = false;

	//	�޼��� ����ü �ʱ�ȭ
	ZeroMemory(&msg, sizeof(MSG));

	//	����޼����� �߻��� �� ���� ������ ����
	while (!done)
	{
		//	������ �޼��� ó��
		if (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//	������ ����޼��� �߻��� ��� ����
		if (msg.message == WM_QUIT)
		{
			done = true;
		}

		// �� �ܿ��� �������� ó��, ���� �ڵ��ϴ� �κ�
		else
		{
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}
	}

	return;
}

bool SystemClass::Frame()
{
	bool result = false;

	//	ESC�� ���� �����츦 �����Ұ��� üũ
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	//	�װ� �ƴ϶�� �׷��� ��ü�� ������ ó��
	result = m_Graphics->Frame();
	if (!result)
	{
		return false;
	}

	return true;
}

LRESULT SystemClass::MyWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//	Ű�� ���ȴ��� üũ
		case WM_KEYDOWN:
		{
			m_Input->KeyDown((unsigned int)wParam);
		}break;

		//	Ű�� �����Ǿ����� üũ
		case WM_KEYUP:
		{
			m_Input->KeyUp((unsigned int)wParam);
		}break;

		//	�� ���� �޼����� �⺻ �޼��� ó���� �ѱ��.
		default:
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}

	return LRESULT();
}

void SystemClass::InitWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE screenSet;
	int posX, posY;

	//	�ܺ������� ��ü�� ���� ��ü�� ����
	AppHandle = this;

	//	�� ���α׷��� �ν��Ͻ��� ���´�.
	m_hInst = GetModuleHandle(nullptr);

	//	���α׷��� �̸� ����
	m_appName = L"�����ӿ�ũ";

	//	������ Ŭ������ ���� ����
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInst;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_appName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//	������ Ŭ���� ���
	RegisterClassEx(&wc);

	//	�ػ� ����
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//	��üȭ��/â��� ����
	if (FULL_SCREEN)
	{
		//	���� ��üȭ���� ��� ����� ����ũž�� �ִ� ũ��� 32bit�� ����
		memset(&screenSet, 0, sizeof(screenSet));
		screenSet.dmSize = sizeof(screenSet);
		screenSet.dmPanningWidth = (unsigned long)screenWidth;
		screenSet.dmPanningHeight = (unsigned long)screenHeight;
		screenSet.dmBitsPerPel = 32;
		screenSet.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//	���÷��� ������ ��üȭ������ ����
		ChangeDisplaySettings(&screenSet, CDS_FULLSCREEN);

		//	â�� ��ġ�� ����
		posX = 0;
		posY = 0;
	}
	else
	{
		//	���� ������ ����� ��� �ػ󵵸� 1280 X 720���� ����
		screenWidth = 1280;
		screenHeight = 720;

		//	â ��ġ �߾� ��ġ
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//	���Ǹ� ���� ������...(�ɼ� �÷��� ������ �� ���� ����...)
	int op = WS_EX_APPWINDOW;
	int op2 = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;

	//	���� �������� ������ â�� �����ϰ� ������ �ڵ��� ���´�.
	m_hWnd = CreateWindowEx(op, m_appName, m_appName, op2, posX, posY, screenWidth, screenHeight, nullptr, nullptr, m_hInst, nullptr);

	//	������ â�� ���� ��Ŀ�� ����
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	//	���콺 Ŀ�� ���ܹ�����~
	ShowCursor(true);

	return;
}

void SystemClass::ShutdownWindows()
{
	//	���콺 Ŀ�� ����������~
	ShowCursor(true);

	//	��üȭ���� �����ϴ� ��� ���÷��� ���� �ʱ�ȭ
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(nullptr, 0);
	}

	//	������ ����(�ı�)
	DestroyWindow(m_hWnd);
	m_hWnd = nullptr;

	//	�� ���α׷��� �ν��Ͻ� ����
	UnregisterClass(m_appName, m_hInst);
	m_hInst = nullptr;

	//	�ܺ� ��ü ������ �ʱ�ȭ
	AppHandle = nullptr;

	return;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//	�����찡 ����Ǿ����� üũ
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;

		//	�����찡 �������� üũ
		case WM_CLOSE:
		{
			PostQuitMessage(0);
		}break;

		//	�� ���� ��� �޼������� �⺻ �޼��� ó���� �ѱ��.
		default:
		{
			return AppHandle->MyWndProc(hWnd, msg, wParam, lParam);
		}
	}

	return LRESULT();
}