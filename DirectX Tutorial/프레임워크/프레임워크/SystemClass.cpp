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
	//	m_Graphics 객체 반환
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Input;
		m_Graphics = 0;
	}

	//	m_Input 객체 반환
	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	//	Window 종료 처리
	ShutdownWindows();
}

void SystemClass::Run()
{
	//	메시지 구조체 생성 및 초기화
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//	사용자로부터 종료 메시지를 받을때까지 메시지 루프를 돕니다.
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			//	종료 메시지를 받을 경우 메시지 루프를 탈출합니다.
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//	그 외에는 Frame 함수를 처리합니다.
			if (!Frame()) break;
		}
	}
}

bool SystemClass::Frame()
{
	//	ESC 키 감지 및 종료 여부를 처리합니다.
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	//	그래픽 객체의 Frame을 처리합니다.
	return m_Graphics->Frame();
}

LRESULT SystemClass::MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	키보드가 눌려졌는가 처리
		case WM_KEYDOWN:
		{
			//	키 눌림 flag를 m_Input 객체에 처리하도록 합니다.
			m_Input->KeyDown((unsigned int)wParam);
			return 0;
		}

		//	키보드가 떨어졌는가 처리
		case WM_KEYUP:
		{
			//	키 해제 flag를 m_Input 객체에 처리하도록 합니다.
			m_Input->KeyUp((unsigned int)wParam);
			return 0;
		}

		//	그 외의 모든 메시지들은 기본 메시지 처리로 넘깁니다.
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	//	외부 포인터를 이 객체로 지정합니다.
	ApplicationHandle = this;

	//	이 프로그램의 인스턴스를 가져옵니다.
	m_hInst = GetModuleHandle(nullptr);

	//	프로그램 이름을 지정합니다.
	m_WinName = L"DX11 FrameWork";

	//	windows 클래스를 아래와 같이 설정합니다.
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

	//	windows class를 등록합니다.
	RegisterClassEx(&wc);

	//	모니터 화면의 해상도를 읽어옵니다.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int posX = 0;
	int posY = 0;

	//	FULL_SCREEN 변수 값에 따라 화면을 설정합니다.
	if (FULL_SCREEN)
	{
		//	풀스크린 모드로 지정했다면 모니터 화면 해상도를 테스크톱 해상도로 지정하고 색상을 32bit로 지정합니다.
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPanningWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPanningHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//	풀스크린으로 디스플레이 설정을 변경합니다.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		//	윈도우 모두의 경우 800 * 600 크기를 지정합니다.
		screenWidth = 800;
		screenHeight = 600;

		//	윈도우 창을 가로, 세로의 정 가운데 오도록 합니다.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//	윈도우를 생성하고 핸들을 구합니다.
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_WinName, m_WinName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, posX, posY, screenWidth, screenHeight, nullptr, nullptr, m_hInst, nullptr);

	//	윈도우를 화면에 표시하고 포커스를 지정합니다.
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
}

void SystemClass::ShutdownWindows()
{
	//	풀스크린 모드였다면 디스플레이 설정을 초기화합니다.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(nullptr, 0);
	}

	//	창을 제거합니다.
	DestroyWindow(m_hWnd);
	m_hWnd = nullptr;

	//	프로그램 인스턴스를 제거합니다.
	UnregisterClass(m_WinName, m_hInst);

	//	외부포인터 참조를 초기화합니다.
	m_WinName = nullptr;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	윈도우 종료를 확인합니다.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		//	윈도우가 닫히는지 확인합니다.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		//	그 외의 모든 메시지들은 시스템 클래스의 메시지 처리로 넘깁니다.
		default:
		{
			return ApplicationHandle->MyWndProc(hWnd, message, wParam, lParam);
		}
	}
}
