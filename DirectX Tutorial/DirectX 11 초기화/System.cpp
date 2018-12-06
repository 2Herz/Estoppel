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
	//	윈도우 창 가로, 세로 넓이 변수 초기화
	int screenWidth = 0;
	int screenHeight = 0;

	//	윈도우 생성 초기화
	InitializeWindows(screenWidth, screenHeight);

	//	m_Input 객체 생성. 이 클래스는 추후 사용자의 키보드 입력 처리에 사용됨
	m_Input = new Input;
	if (!m_Input)
	{
		return false;
	}

	//	m_Input 객체 초기화
	m_Input->Initialize();

	//	m_Graphics 객체 생성. 그래픽 랜더링을 처리하기 위한 객체임
	m_Graphics = new Graphics;
	if (!m_Graphics)
	{
		return false;
	}

	//	m_Graphics 객체 초기화.
	return m_Graphics->Initialize(screenWidth, screenHeight, m_hWnd);
}

void System::Shutdown()
{
	//	m_Graphics 객체 반환
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
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

void System::Run()
{
	//	메시지 구조체 생성 및 초기화
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//	사용자로부터 종료 메시지를 받을때까지 메시지루프를 돔
	while (true)
	{
		//	윈도우 메시지 처리
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			//	종료 메시지를 받을 경우 메시지 루프 탈출
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//	그 외의 경우에는 Frame() 함수를 실행
			if (!Frame()) break;
		}
	}
}

bool System::Frame()
{
	//	ESC 키 감지 및 종료 여부 처리
	if (m_Input->IsKeyDown(VK_ESCAPE)) return false;

	//	그래픽 객체의 Frame() 함수를 실행
	return m_Graphics->Frame();
}

LRESULT CALLBACK System::MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	키 입력 관련 처리
		//	눌렀을 때
	case WM_KEYDOWN:
	{
		//	키가 눌렸을 때 m_Input 객체가 처리
		m_Input->KeyDown((unsigned int)wParam);
		return 0;
	}
	//	키를 뗐을 때
	case WM_KEYUP:
	{
		//	키가 해제될 때 m_Input 객체가 처리
		m_Input->KeyUp((unsigned int)wParam);
		return 0;
	}
	//	그 외 모든 메시지 처리를 기본 메시지 처리로 넘김
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
}

void System::InitializeWindows(int& screenWidth, int& screenHeight)
{
	//	외부 포인터를 이 객체로 설정
	Handle = this;

	//	인스턴스를 얻어온다.
	m_hInst = GetModuleHandle(nullptr);

	//	프로그램의 이름을 설정
	m_WinName = L"Direct X 초기화";

	//	Window Class 설정
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

	//	Window Class 등록
	RegisterClassEx(&wc);

	//	모니터 해상도 얻어오기
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int posX = 0;
	int posY = 0;

	//	FULL_SCREEN 변수 값에 따라 화면설정
	if (FULL_SCREEN)
	{
		//	최대화면 상태일 때 모니터 화면 해상도를 데스크탑 해상도로 설정하고 색상을 32bit로 설정
		DEVMODE ScreenSetting;
		memset(&ScreenSetting, 0, sizeof(ScreenSetting));
		ScreenSetting.dmSize = sizeof(ScreenSetting);
		ScreenSetting.dmPelsWidth = (unsigned long)screenWidth;
		ScreenSetting.dmPelsHeight = (unsigned long)screenHeight;
		ScreenSetting.dmBitsPerPel = 32;
		ScreenSetting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//	최대화면으로 변경
		ChangeDisplaySettings(&ScreenSetting, CDS_FULLSCREEN);
	}
	else
	{
		//	윈도우 모드의 경우 800, 600 크기로 설정
		screenWidth = 800;
		screenHeight = 600;

		//	윈도우 창을 가로, 세로의 정 가운데 오도록 설정
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//	윈도우 창 생성
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_WinName, m_WinName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, nullptr, nullptr, m_hInst, nullptr);

	//	실제 생성된 윈도우 창을 화면에 출력하고 포커스 설정
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
}

void System::ShutdownWindows()
{
	//	최대화면 상태였다면 디스플레이 설정 초기화
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(nullptr, 0);
	}

	//	윈도우 창 제거
	DestroyWindow(m_hWnd);
	m_hWnd = nullptr;

	//	인스턴스 제거
	UnregisterClass(m_WinName, m_hInst);
	m_hInst = nullptr;

	//	외부 포인터 초기화(윈도우객체초기화)
	//	윈도우 객체를 이 포인터로 설정했기 때문에...
	Handle = nullptr;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	윈도우 종료 확인
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	//	윈도우가 닫혔는지 확인
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	//	그 외의 모든 메시지는 시스템 클래스의 메시지 처리로 넘김
	default:
	{
		return Handle->MyWndProc(hWnd, message, wParam, lParam);
	}
	}
}