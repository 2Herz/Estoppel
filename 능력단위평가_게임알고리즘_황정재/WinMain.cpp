#include "stdafx.h"
#include "SceneMgr.h"

Monster npc;

FPOINT g_PlayerPos = { 100, 100 };
FPOINT g_MousePos = { 100, 100 };
int g_speed = 150;

VOID Update(float _elapseTime)
{
	FPOINT vec = g_MousePos - g_PlayerPos;

	if (vec.Dist() > 5)
	{
		FPOINT	dir = vec.Nomal();
		g_PlayerPos = g_PlayerPos + dir * _elapseTime * g_speed;
	}

	npc.Update(_elapseTime);
}
VOID Render(HDC _hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hOldBrush = SelectBrush(_hdc, hBrush);

	RECT rt = g_PlayerPos.GetRect(50);
	Ellipse(_hdc, rt.left, rt.top, rt.right, rt.bottom);
	DeleteObject(SelectBrush(_hdc, hOldBrush));

	//	NPC
	npc.Render(_hdc);
}

LRESULT	CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_LBUTTONDOWN:
	{
		g_MousePos = FPOINT(GET_X_LPARAM(_lParam), GET_Y_LPARAM(_lParam));
	}break;
	case WM_RBUTTONDOWN:
	{
		FPOINT pos = FPOINT(GET_X_LPARAM(_lParam), GET_Y_LPARAM(_lParam));
	}break;

	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		default:
			break;
		}
	}break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;

	}

	return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}

int APIENTRY WinMain(HINSTANCE _hInst, HINSTANCE _hPrevInst, LPSTR _CmdParam, int _CmdShow)		
{
	LPCSTR		g_className		= "HOW";
	WNDCLASS	wndClass		= {};

	//	정보입력
	wndClass.lpszClassName		= g_className;
	wndClass.hInstance			= _hInst;
	wndClass.lpfnWndProc		= WndProc;

	wndClass.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor			= LoadCursor(nullptr, IDC_ARROW);		
	wndClass.hIcon				= LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClass(&wndClass);

	int		wsOption	= WS_OVERLAPPEDWINDOW;
	RECT	rt			= { 0, 0, WIN_WIDTH, WIN_HEIGHT };

	AdjustWindowRect(&rt, wsOption, FALSE);
	OffsetRect(&rt, -rt.left, -rt.top);

	HWND hWnd = CreateWindow( 
		g_className, g_winName, wsOption, 
		0, 0, rt.right, rt.bottom,
		nullptr, nullptr, _hInst, nullptr);					

	if (hWnd == nullptr)
	{
		return 0;
	}

	ShowWindow(hWnd, _CmdShow);

	timeBeginPeriod(1);

	MSG	msg = {};

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			
			DispatchMessage(&msg);
		}
		else
		{
			static float	timeElapsed		= 0.0f;
			static long		lastTime		= timeGetTime();
			static long		nowTime			= lastTime;

			do
			{
				nowTime = timeGetTime();
				timeElapsed = (nowTime - lastTime) * 0.001f;
			} while (timeElapsed <= 1.0f/60 );
			
			lastTime = nowTime;

			Update(timeElapsed);

			HDC		hdc		= GetDC(hWnd);
			HDC		backHdc	= CreateCompatibleDC(hdc);
			HBITMAP backBit = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
			HBITMAP oldBit	= SelectBitmap(backHdc, backBit);
			FillRect(backHdc, &rt, GetStockBrush(WHITE_BRUSH));

			Render(backHdc);
			
			BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, backHdc, 0, 0, SRCCOPY);

			DeleteObject(SelectBitmap(backHdc, oldBit));
			DeleteDC(backHdc);
			ReleaseDC(hWnd, hdc);
		}
	}

	timeEndPeriod(1);

	return msg.wParam;
}
