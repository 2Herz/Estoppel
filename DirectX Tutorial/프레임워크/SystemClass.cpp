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
	//	함수에 인자로 넘기기위한 변수들, 위도우 가로 및 세로 변수 초기화
	int screenWidth = 0;
	int screenHeight = 0;
	bool result = false;

	//	윈도우 API 초기화
	InitWindows(screenWidth, screenHeight);

	//	입력 객체 생성-> 이 객체는 사용자의 키보드 입력의 모든 처리에 사용
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	//	입력 객체 초기화
	m_Input->Init();

	//	그래픽 객체 생성-> 이 객체는 이 프로그램의 모든 그래픽 랜더링 처리에 사용
	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}

	//	그래픽 객체 초기화
	result = m_Graphics->Init(screenWidth, screenHeight, m_hWnd);
	if (!result)
	{
		return false;
	}

	return true;
}

void SystemClass::Shutdown()
{
	//	그래픽 객체 메모리 해제
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = nullptr;
	}

	//	입력 객체 메모리 해제
	if (m_Input)
	{
		delete m_Input;
		m_Input = nullptr;
	}

	//	윈도우 종료
	ShutdownWindows();
}

void SystemClass::Run()
{
	MSG msg;
	bool done = false;
	bool result = false;

	//	메세지 구조체 초기화
	ZeroMemory(&msg, sizeof(MSG));

	//	종료메세지가 발생할 때 까지 루프를 돌림
	while (!done)
	{
		//	윈도우 메세지 처리
		if (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//	윈도우 종료메세지 발생할 경우 종료
		if (msg.message == WM_QUIT)
		{
			done = true;
		}

		// 그 외에는 프레임을 처리, 실제 코딩하는 부분
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

	//	ESC를 통해 윈도우를 종료할건지 체크
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	//	그게 아니라면 그래픽 객체의 프레임 처리
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
		//	키가 눌렸는지 체크
		case WM_KEYDOWN:
		{
			m_Input->KeyDown((unsigned int)wParam);
		}break;

		//	키가 해제되었는지 체크
		case WM_KEYUP:
		{
			m_Input->KeyUp((unsigned int)wParam);
		}break;

		//	그 외의 메세지는 기본 메세지 처리로 넘긴다.
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

	//	외부포인터 객체를 현재 객체로 설정
	AppHandle = this;

	//	이 프로그램의 인스턴스를 얻어온다.
	m_hInst = GetModuleHandle(nullptr);

	//	프로그램의 이름 설정
	m_appName = L"프레임워크";

	//	윈도우 클래스의 정보 설정
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

	//	윈도우 클래스 등록
	RegisterClassEx(&wc);

	//	해상도 설정
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//	전체화면/창모드 설정
	if (FULL_SCREEN)
	{
		//	만약 전체화면일 경우 사용자 데스크탑의 최대 크기와 32bit로 설정
		memset(&screenSet, 0, sizeof(screenSet));
		screenSet.dmSize = sizeof(screenSet);
		screenSet.dmPanningWidth = (unsigned long)screenWidth;
		screenSet.dmPanningHeight = (unsigned long)screenHeight;
		screenSet.dmBitsPerPel = 32;
		screenSet.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//	디스플레이 설정을 전체화면으로 변경
		ChangeDisplaySettings(&screenSet, CDS_FULLSCREEN);

		//	창의 위치를 설정
		posX = 0;
		posY = 0;
	}
	else
	{
		//	만약 윈도우 모드일 경우 해상도를 1280 X 720으로 설정
		screenWidth = 1280;
		screenHeight = 720;

		//	창 위치 중앙 배치
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//	편의를 위한 변수등...(옵션 플래그 일일히 다 적기 귀찮...)
	int op = WS_EX_APPWINDOW;
	int op2 = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;

	//	위의 설정으로 윈도우 창을 생성하고 윈도우 핸들을 얻어온다.
	m_hWnd = CreateWindowEx(op, m_appName, m_appName, op2, posX, posY, screenWidth, screenHeight, nullptr, nullptr, m_hInst, nullptr);

	//	윈도우 창을 띄우고 포커스 설정
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	//	마우스 커서 숨겨버리기~
	ShowCursor(true);

	return;
}

void SystemClass::ShutdownWindows()
{
	//	마우스 커서 보여버리기~
	ShowCursor(true);

	//	전체화면을 종료하는 경우 디스플레이 설정 초기화
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(nullptr, 0);
	}

	//	윈도우 삭제(파괴)
	DestroyWindow(m_hWnd);
	m_hWnd = nullptr;

	//	이 프로그램의 인스턴스 삭제
	UnregisterClass(m_appName, m_hInst);
	m_hInst = nullptr;

	//	외부 객체 포인터 초기화
	AppHandle = nullptr;

	return;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//	윈도우가 종료되었는지 체크
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;

		//	윈도우가 닫히는지 체크
		case WM_CLOSE:
		{
			PostQuitMessage(0);
		}break;

		//	그 외의 모든 메세지들은 기본 메세지 처리로 넘긴다.
		default:
		{
			return AppHandle->MyWndProc(hWnd, msg, wParam, lParam);
		}
	}

	return LRESULT();
}