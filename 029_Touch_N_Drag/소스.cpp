#undef UNICODE
#include <Windows.h>
#include <windowsx.h>
#include <sstream>
#include <iomanip>

#include "TimeMgr.h"
#include "ImgClass.h"

LPCSTR		g_winName		= "HOW-SAMPLEWINDOW";

const int WIN_WIDTH			= 800;
const int WIN_HEIGHT		= 600;

POINT		g_StartPos = { 100, 90 };
SIZE		g_Size = { 3, 3 };
int			g_CellSize = 100;
int			g_LineWidth = 5;
COLORREF	g_LineColor = RGB(100, 0, 255);

POINT		g_PiecePos = {400, 300};

POINT		g_MagnetPos = { 0, 0 };


void Init(HWND _hWnd)
{
}
void Release()
{
}
void Update(float _elapseTime)
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		g_PiecePos.x-= 3;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		g_PiecePos.x+= 3;
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		g_PiecePos.y -= 3;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		g_PiecePos.y += 3;
	}
}
void Render(HDC _hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, g_LineWidth, g_LineColor);
	HPEN hOld = SelectPen(_hdc, hPen);

	//	가로선
	for (long y = 0; y <= g_Size.cy; y++)
	{
		//	시작 x 좌표 + 0, 시작 y 좌표 + 칸사이즈 * y 좌표
		MoveToEx(_hdc, g_StartPos.x + 0, g_StartPos.y + g_CellSize * y, nullptr);
		//	시작 x 좌표 + 칸사이즈 * 사이즈 x 좌표, 시작 y 좌표 + 칸사이즈 * y
		LineTo(_hdc, g_StartPos.x + g_CellSize * g_Size.cx, g_StartPos.y + g_CellSize * y);
	}

	//	세로선
	for (long x = 0; x <= g_Size.cx; x++)
	{
		//	시작 x 좌표 + 칸사이즈 * x 좌표, 시작 y 좌표 + 0
		MoveToEx(_hdc, g_StartPos.x + g_CellSize * x, g_StartPos.y + 0, nullptr);
		//	시작 x 좌표 + 칸사이즈, 시작 y 좌표 + 칸사이즈 * y
		LineTo(_hdc, g_StartPos.x + g_CellSize * x, g_StartPos.y + g_CellSize * g_Size.cy);
	}

	DeleteObject(SelectPen(_hdc, hOld));

	RECT rt = { 0, 0, g_CellSize, g_CellSize };

	OffsetRect(&rt, g_PiecePos.x, g_PiecePos.y);

	Rectangle(_hdc, rt.left, rt.top, rt.right, rt.bottom);

	TIME.Render(_hdc, 0, 0);
}

//	콜백함수 : 윈도우가 대신 호출해준다.
LRESULT	CALLBACK WndProc(
	HWND		_hWnd, 
	UINT		_message, 
	WPARAM		_wParam, 
	LPARAM		_lParam)
{
	switch (_message)
	{
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case VK_SPACE:
		{
			//	윈도우화면에서의 해당 좌표
			POINT RealMagnetPos = { g_StartPos.x + g_CellSize * g_MagnetPos.x, g_StartPos.y + g_CellSize * g_MagnetPos.y };

			//	sqrt((x-x0)^2 + (y-y0)^2)
			float distance = sqrtf(powf(RealMagnetPos.x - g_PiecePos.x, 2) + powf(RealMagnetPos.y - g_PiecePos.y, 2));

			if (distance < 30)
			{
				g_PiecePos.x = RealMagnetPos.x;
				g_PiecePos.y = RealMagnetPos.y;
			}

		}break;

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


int APIENTRY WinMain(
	HINSTANCE	_hInst,			//	프로세스 핸들
	HINSTANCE	_hPrevInst,		//	이전 프로세스 핸들( 현재 안씀 )
	LPSTR		_CmdParam,		//	명령줄 인수( char* )
	int			_CmdShow)		//	기본창 상태
{
	LPCSTR	g_className		= "HOW";

	//	1. 윈도우 클래스 정의 및 등록
	WNDCLASS	wndClass	= {};

	//	정보입력
	wndClass.lpszClassName	= g_className;
	wndClass.hInstance		= _hInst;
	wndClass.lpfnWndProc	= WndProc;	//	함수포인터

	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//	배경색
	wndClass.hCursor		= LoadCursor(nullptr, IDC_ARROW);		//	커서모양
	wndClass.hIcon			= LoadIcon(nullptr, IDI_APPLICATION);	//	아이콘

	//wndClass.style			= CS_HREDRAW | CS_VREDRAW;			//	비트플래그

	RegisterClass(&wndClass);

	//	실제 윈도우 크기 구하기
	int		wsOption	= WS_OVERLAPPEDWINDOW;
	RECT	rt			= { 0, 0, WIN_WIDTH, WIN_HEIGHT };

	//	윈도우 기본 옵션에 따른 실제 기본창 크기
	AdjustWindowRect(&rt, wsOption, FALSE);

	//	2. 윈도우 생성 및 화면 띄우기
	HWND hWnd = CreateWindow(
		g_className,				//	위의 윈도우클래스 이름
		g_winName,					//	윈도우 타이틀
		wsOption,					//	윈도우 기본 옵션( 캡션바, 최대화버튼, 최소버튼. )
		0, 0,					//	윈도우 시작 위치
		rt.right - rt.left, rt.bottom - rt.top,	//	윈도우 크기
		nullptr,					//	부모윈도우핸들
		nullptr,					//	메뉴핸들
		_hInst,						//	연결할 프로세스핸들
		nullptr);					//	무쓸모...

	if (hWnd == nullptr)
	{
		return 0;
	}

	//	초기화
	Init(hWnd);

	ShowWindow(hWnd, _CmdShow);

	//	3. 메시지 루프( 고객센터 )
	MSG	msg = {};

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			//	탈출조건
			if (msg.message == WM_QUIT) break;

			//	메시지가 발생한 경우
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update(TIME.Tick());

			ImgClass	back(hWnd, WIN_WIDTH, WIN_HEIGHT);
			//	새로운 DC에 이미지를 그린다.
			Render(back.GetImgDC());
			//	화면 hdc 에 백버퍼 이미지를 그린다.
			back.Render(hWnd);
		}
	}

	//	해제처리
	Release();

	return msg.wParam;
}