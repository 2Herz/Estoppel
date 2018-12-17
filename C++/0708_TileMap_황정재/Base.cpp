#undef UNICODE
#include "Base.h"
#include "TimeManager.h"
#include "ImageManager.h"

Base *pMain = nullptr;

LRESULT CALLBACK MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return pMain->WndProc(hWnd, message, wParam, lParam);
}

VOID Base::RegWin()
{	//	1. 윈도우 클래스 정의 및 등록
	WNDCLASS	myWnd = {};

	//	정보입력
	myWnd.lpszClassName = m_ClassName.c_str();
	myWnd.hInstance = m_hInst;
	myWnd.lpfnWndProc = MyWndProc;
	myWnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	myWnd.hCursor = LoadCursor(nullptr, IDC_ARROW);
	myWnd.hIcon = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClass(&myWnd);
}

BOOL Base::CreateWin()
{
	pMain = this;
	int		wsOption = WS_OVERLAPPEDWINDOW;
	RECT	rt = { 0, 0, m_WinSize.cx, m_WinSize.cy };

	AdjustWindowRect(&rt, wsOption, FALSE);

	m_hWnd = CreateWindow(m_ClassName.c_str(), m_WinName.c_str(), wsOption, 0, 0, rt.right - rt.left, rt.bottom - rt.top, nullptr, nullptr, m_hInst, nullptr);

	if (m_hWnd == nullptr)
	{
		pMain = nullptr;
		return FALSE;
	}

	Init(m_hWnd);

	ShowWindow(m_hWnd, SW_SHOW);

	return TRUE;
}

VOID Base::Init(HWND hWnd)
{
	return VOID();
}

VOID Base::Release()
{
	return VOID();
}

VOID Base::Update(float elapseTime)
{
	return VOID();
}

VOID Base::Render(HDC hdc)
{
	return VOID();
}

LRESULT Base::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{
					if (IDYES == MessageBox(hWnd, "종료하시겠습니까?", "Quit", MB_YESNO))
					{
						PostQuitMessage(0);
					}
					else if (IDNO)
					{
						break;
					}
				}break;
			}
		}break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

int Base::MessageLoop()
{
	MSG msg = {};

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update(TIME.Tick());
			Img back(m_hWnd, m_WinSize.cx, m_WinSize.cy);
			Render(back.GetImgDC());
			back.Render(m_hWnd);
		}
	}

	Release();
	return 0;
}

BOOL Base::NewWin(HINSTANCE hInst, int width, int height, LPCSTR winName)
{
	m_hInst = hInst;

	m_WinSize.cx = width;
	m_WinSize.cy = height;

	m_ClassName = winName;
	m_WinName = winName;

	RegWin();

	if (CreateWin() == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}