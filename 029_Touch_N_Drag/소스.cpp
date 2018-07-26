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


POINT		g_PiecePos1 = {400, 300};
POINT		g_PiecePos2 = {410, 300};
POINT		g_PiecePos3 = {420, 300};
POINT		g_PiecePos4 = {430, 300};
POINT		g_PiecePos5 = {440, 300};
POINT		g_PiecePos6 = {450, 300};
POINT		g_PiecePos7 = {460, 300};
POINT		g_PiecePos8 = {470, 300};
POINT		g_PiecePos9 = {480, 300};

POINT		g_MagnetPos1 = { 0, 0 };
POINT		g_MagnetPos2 = { 0, 1 };
POINT		g_MagnetPos3 = { 0, 2 };
POINT		g_MagnetPos4 = { 1, 0 };
POINT		g_MagnetPos5 = { 1, 1 };
POINT		g_MagnetPos6 = { 1, 2 };
POINT		g_MagnetPos7 = { 2, 0 };
POINT		g_MagnetPos8 = { 2, 1 };
POINT		g_MagnetPos9 = { 2, 2 };


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
		g_PiecePos1.x-= 1;
		g_PiecePos2.x-= 1;
		g_PiecePos3.x-= 1;
		g_PiecePos4.x-= 1;
		g_PiecePos5.x-= 1;
		g_PiecePos6.x-= 1;
		g_PiecePos7.x-= 1;
		g_PiecePos8.x-= 1;
		g_PiecePos9.x-= 1;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		g_PiecePos1.x+= 1;
		g_PiecePos2.x+= 1;
		g_PiecePos3.x+= 1;
		g_PiecePos4.x+= 1;
		g_PiecePos5.x+= 1;
		g_PiecePos6.x+= 1;
		g_PiecePos7.x+= 1;
		g_PiecePos8.x+= 1;
		g_PiecePos9.x+= 1;
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		g_PiecePos1.y -= 1;
		g_PiecePos2.y -= 1;
		g_PiecePos3.y -= 1;
		g_PiecePos4.y -= 1;
		g_PiecePos5.y -= 1;
		g_PiecePos6.y -= 1;
		g_PiecePos7.y -= 1;
		g_PiecePos8.y -= 1;
		g_PiecePos9.y -= 1;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		g_PiecePos1.y += 1;
		g_PiecePos2.y += 1;
		g_PiecePos3.y += 1;
		g_PiecePos4.y += 1;
		g_PiecePos5.y += 1;
		g_PiecePos6.y += 1;
		g_PiecePos7.y += 1;
		g_PiecePos8.y += 1;
		g_PiecePos9.y += 1;
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

	RECT rt1 = { 0, 0, g_CellSize, g_CellSize };
	RECT rt2 = { 0, 0, g_CellSize, g_CellSize };
	RECT rt3 = { 0, 0, g_CellSize, g_CellSize };
	RECT rt4 = { 0, 0, g_CellSize, g_CellSize };
	RECT rt5 = { 0, 0, g_CellSize, g_CellSize };
	RECT rt6 = { 0, 0, g_CellSize, g_CellSize };
	RECT rt7 = { 0, 0, g_CellSize, g_CellSize };
	RECT rt8 = { 0, 0, g_CellSize, g_CellSize };
	RECT rt9 = { 0, 0, g_CellSize, g_CellSize };

	OffsetRect(&rt1, g_PiecePos1.x, g_PiecePos1.y);
	OffsetRect(&rt2, g_PiecePos2.x, g_PiecePos2.y);
	OffsetRect(&rt3, g_PiecePos3.x, g_PiecePos3.y);
	OffsetRect(&rt4, g_PiecePos4.x, g_PiecePos4.y);
	OffsetRect(&rt5, g_PiecePos5.x, g_PiecePos5.y);
	OffsetRect(&rt6, g_PiecePos6.x, g_PiecePos6.y);
	OffsetRect(&rt7, g_PiecePos7.x, g_PiecePos7.y);
	OffsetRect(&rt8, g_PiecePos8.x, g_PiecePos8.y);
	OffsetRect(&rt9, g_PiecePos9.x, g_PiecePos9.y);

	Rectangle(_hdc, rt1.left, rt1.top, rt1.right, rt1.bottom);
	Rectangle(_hdc, rt2.left, rt2.top, rt2.right, rt2.bottom);
	Rectangle(_hdc, rt3.left, rt3.top, rt3.right, rt3.bottom);
	Rectangle(_hdc, rt4.left, rt4.top, rt4.right, rt4.bottom);
	Rectangle(_hdc, rt5.left, rt5.top, rt5.right, rt5.bottom);
	Rectangle(_hdc, rt6.left, rt6.top, rt6.right, rt6.bottom);
	Rectangle(_hdc, rt7.left, rt7.top, rt7.right, rt7.bottom);
	Rectangle(_hdc, rt8.left, rt8.top, rt8.right, rt8.bottom);
	Rectangle(_hdc, rt9.left, rt9.top, rt9.right, rt9.bottom);

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
			POINT RealMagnetPos1 = { g_StartPos.x + g_CellSize * g_MagnetPos1.x, g_StartPos.y + g_CellSize * g_MagnetPos1.y };
			POINT RealMagnetPos2 = { g_StartPos.x + g_CellSize * g_MagnetPos1.x, g_StartPos.y + g_CellSize * g_MagnetPos1.y };
			POINT RealMagnetPos3 = { g_StartPos.x + g_CellSize * g_MagnetPos1.x, g_StartPos.y + g_CellSize * g_MagnetPos1.y };
			POINT RealMagnetPos4 = { g_StartPos.x + g_CellSize * g_MagnetPos1.x, g_StartPos.y + g_CellSize * g_MagnetPos1.y };
			POINT RealMagnetPos5 = { g_StartPos.x + g_CellSize * g_MagnetPos1.x, g_StartPos.y + g_CellSize * g_MagnetPos1.y };
			POINT RealMagnetPos6 = { g_StartPos.x + g_CellSize * g_MagnetPos1.x, g_StartPos.y + g_CellSize * g_MagnetPos1.y };
			POINT RealMagnetPos7 = { g_StartPos.x + g_CellSize * g_MagnetPos1.x, g_StartPos.y + g_CellSize * g_MagnetPos1.y };
			POINT RealMagnetPos8 = { g_StartPos.x + g_CellSize * g_MagnetPos1.x, g_StartPos.y + g_CellSize * g_MagnetPos1.y };
			POINT RealMagnetPos9 = { g_StartPos.x + g_CellSize * g_MagnetPos1.x, g_StartPos.y + g_CellSize * g_MagnetPos1.y };

			//	sqrt((x-x0)^2 + (y-y0)^2)
			float distance1 = sqrtf(powf(RealMagnetPos1.x - g_PiecePos1.x, 2) + powf(RealMagnetPos1.y - g_PiecePos1.y, 2));
			float distance2 = sqrtf(powf(RealMagnetPos2.x - g_PiecePos2.x, 2) + powf(RealMagnetPos2.y - g_PiecePos2.y, 2));
			float distance3 = sqrtf(powf(RealMagnetPos3.x - g_PiecePos3.x, 2) + powf(RealMagnetPos3.y - g_PiecePos3.y, 2));
			float distance4 = sqrtf(powf(RealMagnetPos4.x - g_PiecePos4.x, 2) + powf(RealMagnetPos4.y - g_PiecePos4.y, 2));
			float distance5 = sqrtf(powf(RealMagnetPos5.x - g_PiecePos5.x, 2) + powf(RealMagnetPos5.y - g_PiecePos5.y, 2));
			float distance6 = sqrtf(powf(RealMagnetPos6.x - g_PiecePos6.x, 2) + powf(RealMagnetPos6.y - g_PiecePos6.y, 2));
			float distance7 = sqrtf(powf(RealMagnetPos7.x - g_PiecePos7.x, 2) + powf(RealMagnetPos7.y - g_PiecePos7.y, 2));
			float distance8 = sqrtf(powf(RealMagnetPos8.x - g_PiecePos8.x, 2) + powf(RealMagnetPos8.y - g_PiecePos8.y, 2));
			float distance9 = sqrtf(powf(RealMagnetPos9.x - g_PiecePos9.x, 2) + powf(RealMagnetPos9.y - g_PiecePos9.y, 2));

			if (distance1 < g_CellSize)
			{
				g_PiecePos1.x = RealMagnetPos1.x;
				g_PiecePos1.y = RealMagnetPos2.y;
			}

			else if (distance2 < g_CellSize)
			{
				g_PiecePos2.x = RealMagnetPos2.x;
				g_PiecePos2.y = RealMagnetPos2.y;
			}

			else if (distance3 < g_CellSize)
			{
				g_PiecePos3.x = RealMagnetPos3.x;
				g_PiecePos3.y = RealMagnetPos3.y;
			}
			else if (distance4 < g_CellSize)
			{
				g_PiecePos4.x = RealMagnetPos4.x;
				g_PiecePos4.y = RealMagnetPos4.y;
			}

			else if (distance5 < g_CellSize)
			{
				g_PiecePos5.x = RealMagnetPos5.x;
				g_PiecePos5.y = RealMagnetPos5.y;
			}

			else if (distance6 < g_CellSize)
			{
				g_PiecePos5.x = RealMagnetPos5.x;
				g_PiecePos5.y = RealMagnetPos5.y;
			}

			else if (distance7 < g_CellSize)
			{
				g_PiecePos5.x = RealMagnetPos5.x;
				g_PiecePos5.y = RealMagnetPos5.y;
			}

			else if (distance8 < g_CellSize)
			{
				g_PiecePos5.x = RealMagnetPos5.x;
				g_PiecePos5.y = RealMagnetPos5.y;
			}

			else if (distance9 < g_CellSize)
			{
				g_PiecePos5.x = RealMagnetPos5.x;
				g_PiecePos5.y = RealMagnetPos5.y;
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