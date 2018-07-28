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

	//	���μ�
	for (long y = 0; y <= g_Size.cy; y++)
	{
		//	���� x ��ǥ + 0, ���� y ��ǥ + ĭ������ * y ��ǥ
		MoveToEx(_hdc, g_StartPos.x + 0, g_StartPos.y + g_CellSize * y, nullptr);
		//	���� x ��ǥ + ĭ������ * ������ x ��ǥ, ���� y ��ǥ + ĭ������ * y
		LineTo(_hdc, g_StartPos.x + g_CellSize * g_Size.cx, g_StartPos.y + g_CellSize * y);
	}

	//	���μ�
	for (long x = 0; x <= g_Size.cx; x++)
	{
		//	���� x ��ǥ + ĭ������ * x ��ǥ, ���� y ��ǥ + 0
		MoveToEx(_hdc, g_StartPos.x + g_CellSize * x, g_StartPos.y + 0, nullptr);
		//	���� x ��ǥ + ĭ������, ���� y ��ǥ + ĭ������ * y
		LineTo(_hdc, g_StartPos.x + g_CellSize * x, g_StartPos.y + g_CellSize * g_Size.cy);
	}

	DeleteObject(SelectPen(_hdc, hOld));

	RECT rt = { 0, 0, g_CellSize, g_CellSize };

	OffsetRect(&rt, g_PiecePos.x, g_PiecePos.y);

	Rectangle(_hdc, rt.left, rt.top, rt.right, rt.bottom);

	TIME.Render(_hdc, 0, 0);
}

//	�ݹ��Լ� : �����찡 ��� ȣ�����ش�.
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
			//	������ȭ�鿡���� �ش� ��ǥ
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
	HINSTANCE	_hInst,			//	���μ��� �ڵ�
	HINSTANCE	_hPrevInst,		//	���� ���μ��� �ڵ�( ���� �Ⱦ� )
	LPSTR		_CmdParam,		//	����� �μ�( char* )
	int			_CmdShow)		//	�⺻â ����
{
	LPCSTR	g_className		= "HOW";

	//	1. ������ Ŭ���� ���� �� ���
	WNDCLASS	wndClass	= {};

	//	�����Է�
	wndClass.lpszClassName	= g_className;
	wndClass.hInstance		= _hInst;
	wndClass.lpfnWndProc	= WndProc;	//	�Լ�������

	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//	����
	wndClass.hCursor		= LoadCursor(nullptr, IDC_ARROW);		//	Ŀ�����
	wndClass.hIcon			= LoadIcon(nullptr, IDI_APPLICATION);	//	������

	//wndClass.style			= CS_HREDRAW | CS_VREDRAW;			//	��Ʈ�÷���

	RegisterClass(&wndClass);

	//	���� ������ ũ�� ���ϱ�
	int		wsOption	= WS_OVERLAPPEDWINDOW;
	RECT	rt			= { 0, 0, WIN_WIDTH, WIN_HEIGHT };

	//	������ �⺻ �ɼǿ� ���� ���� �⺻â ũ��
	AdjustWindowRect(&rt, wsOption, FALSE);

	//	2. ������ ���� �� ȭ�� ����
	HWND hWnd = CreateWindow(
		g_className,				//	���� ������Ŭ���� �̸�
		g_winName,					//	������ Ÿ��Ʋ
		wsOption,					//	������ �⺻ �ɼ�( ĸ�ǹ�, �ִ�ȭ��ư, �ּҹ�ư. )
		0, 0,					//	������ ���� ��ġ
		rt.right - rt.left, rt.bottom - rt.top,	//	������ ũ��
		nullptr,					//	�θ��������ڵ�
		nullptr,					//	�޴��ڵ�
		_hInst,						//	������ ���μ����ڵ�
		nullptr);					//	������...

	if (hWnd == nullptr)
	{
		return 0;
	}

	//	�ʱ�ȭ
	Init(hWnd);

	ShowWindow(hWnd, _CmdShow);

	//	3. �޽��� ����( ������ )
	MSG	msg = {};

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			//	Ż������
			if (msg.message == WM_QUIT) break;

			//	�޽����� �߻��� ���
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update(TIME.Tick());

			ImgClass	back(hWnd, WIN_WIDTH, WIN_HEIGHT);
			//	���ο� DC�� �̹����� �׸���.
			Render(back.GetImgDC());
			//	ȭ�� hdc �� ����� �̹����� �׸���.
			back.Render(hWnd);
		}
	}

	//	����ó��
	Release();

	return msg.wParam;
}