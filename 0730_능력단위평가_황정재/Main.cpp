//	Global Header
#include "Global.h"

//	Global Variables
LPCSTR      g_winName = "능력단위평가";
DWORD		g_LastTime = 0;
int         g_Count = 0;
int         g_SetFPS = 60;
int         g_FPS = 0;
int         g_FPSTime = 0;
POINT		m_MousePos = {};
POINT		g_StartPos = { 450, 100 };
SIZE		g_Size = { 3, 3 };
int			g_CellSize = 100;
int			g_LineWidth = 10;
COLORREF	g_LineColor = RGB(255, 0, 0);
POINT		g_PiecePos[9] = { { 100, 100 } ,{ 200, 100 } ,{ 300, 100 } ,{ 100, 200 } ,{ 200, 200 } ,{ 300, 200 } ,{ 100, 300 } ,{ 200, 300 } ,{ 300, 300 } };
POINT		g_MagnetPos[9] = { { 0, 0 } ,{ 1, 0 } ,{ 2, 0 } ,{ 0, 1 } ,{ 1, 1 } ,{ 2, 1 } ,{ 0, 2 } ,{ 1, 2 } ,{ 2, 2 } };
bool		g_isClick[9] = {};
float		g_CheckPosX = 0;
float		g_CheckPosY = 0;
HDC			g_ImgDC = nullptr;
HBITMAP		g_ImgBit = nullptr;
HBITMAP		g_OldBit = nullptr;
POINT		g_Pos = {};

void Init(HWND _hWnd)
{
	timeBeginPeriod(1);

	g_LastTime = timeGetTime();

	HDC   hdc = GetDC(_hWnd);

	g_ImgDC = CreateCompatibleDC(hdc);
	g_ImgBit = (HBITMAP)LoadImage(nullptr, "Ryan.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	g_OldBit = SelectBitmap(g_ImgDC, g_ImgBit);

	ReleaseDC(_hWnd, hdc);
}
void Release()
{
	timeEndPeriod(1);
	if (g_ImgDC != nullptr)
	{
		DeleteObject(SelectBitmap(g_ImgDC, g_OldBit));
		DeleteDC(g_ImgDC);
	}
}

void Update(DWORD elapseTime)
{
}
void Render(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, g_LineWidth, g_LineColor);
	HPEN hOld = SelectPen(hdc, hPen);

	//   가로선
	for (long y = 0; y <= g_Size.cy; y++)
	{
		MoveToEx(hdc,
			g_StartPos.x + 0,
			g_StartPos.y + g_CellSize * y,
			nullptr);

		LineTo(hdc,
			g_StartPos.x + g_CellSize * g_Size.cx,
			g_StartPos.y + g_CellSize * y);
	}
	//   세로선
	for (long x = 0; x <= g_Size.cx; x++)
	{
		MoveToEx(hdc,
			g_StartPos.x + g_CellSize * x,
			g_StartPos.y + 0,
			nullptr);

		LineTo(hdc,
			g_StartPos.x + g_CellSize * x,
			g_StartPos.y + g_CellSize * g_Size.cy);
	}

	g_Pos = {};
	//   조각
	for (int i = 0; i < 9; i++)
	{
		RECT   rt = { 0, 0, g_CellSize, g_CellSize };
		OffsetRect(&rt, g_PiecePos[i].x, g_PiecePos[i].y);

		//Rectangle(_hdc, rt.left, rt.top, rt.right, rt.bottom);
		if (g_ImgDC != nullptr)
		{
			BitBlt(hdc, rt.left, rt.top, g_CellSize, g_CellSize, g_ImgDC, g_Pos.x, g_Pos.y, SRCCOPY);
		}

		if (g_Pos.x == 200)
		{
			g_Pos.x = 0;
			g_Pos.y += 100;
		}
		else
			g_Pos.x += 100;
	}

	//   해제 및 삭제
	DeleteObject(SelectPen(hdc, hOld));
}

//   콜백
LRESULT   CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_MOUSEMOVE:
		{
			for (int i = 0; i < 9; i++)
			{
				if (g_isClick[i] == true)
				{
					m_MousePos.x = GET_X_LPARAM(lParam);
					m_MousePos.y = GET_Y_LPARAM(lParam);

					float checkPosX = float(GET_X_LPARAM(lParam));
					float checkPosY = float(GET_Y_LPARAM(lParam));

					g_PiecePos[i].x += LONG((checkPosX - g_CheckPosX));
					g_PiecePos[i].y += LONG((checkPosY - g_CheckPosY));

					g_CheckPosX = checkPosX;
					g_CheckPosY = checkPosY;
				}
			}
		}break;

		case WM_RBUTTONDOWN:
		{
			m_MousePos.x = GET_X_LPARAM(lParam);
			m_MousePos.y = GET_Y_LPARAM(lParam);
			for (int i = 0; i < 9; i++)
			{
				if (m_MousePos.x >= g_PiecePos[i].x && m_MousePos.x <= g_PiecePos[i].x + g_CellSize &&
					m_MousePos.y >= g_PiecePos[i].y && m_MousePos.y <= g_PiecePos[i].y + g_CellSize)
				{
					g_isClick[i] = true;
					break;
				}
			}
			g_CheckPosX = float(GET_X_LPARAM(lParam));
			g_CheckPosY = float(GET_Y_LPARAM(lParam));
		}break;

		case WM_RBUTTONUP:
		{
			for (int i = 0; i < 9; i++)
			{
				if (g_isClick[i] == true)
				{
					POINT RealMagnetPos = {
						g_StartPos.x + g_CellSize * g_MagnetPos[i].x,
						g_StartPos.y + g_CellSize * g_MagnetPos[i].y };

					float distance = sqrtf(powf(RealMagnetPos.x - g_PiecePos[i].x, 2) + powf(RealMagnetPos.y - g_PiecePos[i].y, 2));

					if (distance < 15)
					{
						g_PiecePos[i] = RealMagnetPos;
					}
					g_isClick[i] = false;
				}
			}
		}break;

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_ESCAPE:
				if (IDYES == MessageBox(hWnd, "종료하시겠습니까?", "Quit", MB_YESNO))
				{
					PostQuitMessage(0);
				}
				else if (IDNO)
				{
					break;
				}
			}break;
		}break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;

	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


int APIENTRY WinMain(HINSTANCE _hInst, HINSTANCE _hPrevInst, LPSTR _CmdParam, int _CmdShow)
{
	LPCSTR   g_className = g_winName;

	WNDCLASS   wndClass = {};

	wndClass.lpszClassName = g_className;
	wndClass.hInstance = _hInst;
	wndClass.lpfnWndProc = WndProc;

	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClass(&wndClass);

	int      wsOption = WS_OVERLAPPEDWINDOW;
	RECT   rt = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

	AdjustWindowRect(&rt, wsOption, FALSE);

	HWND hWnd = CreateWindow(g_className, g_winName, wsOption, 0, 0, rt.right - rt.left, rt.bottom - rt.top, nullptr, nullptr, _hInst, nullptr);


	if (hWnd == nullptr)
	{
		return 0;
	}

	Init(hWnd);

	ShowWindow(hWnd, _CmdShow);

	MSG   msg = {};

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
			DWORD   elapseTime;
			do
			{
				DWORD   nowTime = timeGetTime();
				elapseTime = nowTime - g_LastTime;

			} while (elapseTime < (1000.0f / g_SetFPS));

			g_FPSTime += elapseTime;
			g_LastTime += elapseTime;
			g_Count++;

			if (g_FPSTime > 1000)
			{
				g_FPS = g_Count;
				g_Count = 0;

				g_FPSTime -= 1000;
			}

			Update(elapseTime);
			HDC         hdc = GetDC(hWnd);
			HDC   backDC = CreateCompatibleDC(hdc);
			HBITMAP hBit = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
			HBITMAP hOldBit = SelectBitmap(backDC, hBit);
			RECT rc = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
			FillRect(backDC, &rc, GetStockBrush(WHITE_BRUSH));
			Render(backDC);
			BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, backDC, 0, 0, SRCCOPY);
			DeleteObject(SelectBitmap(backDC, hOldBit));
			DeleteDC(backDC);

			ReleaseDC(hWnd, hdc);
		}
	}

	Release();
	return msg.wParam;
}