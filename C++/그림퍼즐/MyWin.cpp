#include "MyWin.h"
#include <sstream>

VOID MyWin::Init(HWND _hWnd)
{
}

VOID MyWin::Release()
{
}

VOID MyWin::Update(float _elapseTime)
{
	
}

VOID MyWin::Render(HDC _hdc)
{
	IMG_MGR->SethWnd(m_hWnd);
	IMG_MGR->OpenImg("우왕굳.bmp", (g_Size.cx * g_CellSize), (g_Size.cy * g_CellSize));

	auto img = IMG_MGR->GetImg("우왕굳");

	if (img != nullptr)
	{
		img->SetTrans();
	}

	HPEN hPen = CreatePen(PS_SOLID, g_LineWidth, g_LineColor);
	HPEN hOld = SelectPen(_hdc, hPen);

	BitBlt(_hdc, 100, 100, (g_Size.cx * g_CellSize), (g_Size.cy * g_CellSize), _hdc, g_Size.cx, g_Size.cy, SRCCOPY);

	//	가로선
	for (long y = 0; y <= g_Size.cy; y++)
	{
		MoveToEx(_hdc, g_StartPos.x + 0, g_StartPos.y + g_CellSize * y, nullptr);
		LineTo(_hdc, g_StartPos.x + g_CellSize * g_Size.cx, g_StartPos.y + g_CellSize * y);
	}
	//	세로선
	for (long x = 0; x <= g_Size.cx; x++)
	{
		MoveToEx(_hdc, g_StartPos.x + g_CellSize * x, g_StartPos.y + 0,nullptr);
		LineTo(_hdc, g_StartPos.x + g_CellSize * x, g_StartPos.y + g_CellSize * g_Size.cy);
	}

	//	조각
	for (int i = 0; i < 9; i++)
	{
		RECT	rt = { 0, 0, g_CellSize, g_CellSize };
		OffsetRect(&rt, g_PiecePos[i].x, g_PiecePos[i].y);

		Rectangle(_hdc, rt.left, rt.top, rt.right, rt.bottom);
		
		//	문자열을 조합해서 출력
		std::stringstream	buf;
		buf << "" << i;		
		TextOut(_hdc, rt.left + 20, rt.top + 20, buf.str().c_str(), buf.str().length());
	}

	//	해제 및 삭제
	DeleteObject(SelectPen(_hdc, hOld));
}

LRESULT MyWin::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_MOUSEMOVE:
	{
		for (int i = 0; i < 9; i++)
		{
			//	윈도우화면에서의 해당 좌표
			if (g_isClick[i] == true)
			{
				m_MousePos.x = GET_X_LPARAM(_lParam);
				m_MousePos.y = GET_Y_LPARAM(_lParam);

				float checkPosX = float(GET_X_LPARAM(_lParam));
				float checkPosY = float(GET_Y_LPARAM(_lParam));

				g_PiecePos[i].x += LONG((checkPosX - g_CheckPosX));
				g_PiecePos[i].y += LONG((checkPosY - g_CheckPosY));

				g_CheckPosX = checkPosX;
				g_CheckPosY = checkPosY;
			}
		}
	}break;

	case WM_LBUTTONDOWN:
	{
		m_MousePos.x = GET_X_LPARAM(_lParam);
		m_MousePos.y = GET_Y_LPARAM(_lParam);
		//	어느것이 선택되었는지 판별식 추가
		for (int i = 0; i < 9; i++)
		{
			if (m_MousePos.x >= g_PiecePos[i].x && m_MousePos.x <= g_PiecePos[i].x + g_CellSize &&
				m_MousePos.y >= g_PiecePos[i].y && m_MousePos.y <= g_PiecePos[i].y + g_CellSize)
			{
				g_isClick[i] = true;
				break;
			}
		}
		g_CheckPosX = float(GET_X_LPARAM(_lParam));
		g_CheckPosY = float(GET_Y_LPARAM(_lParam));
	}break;

	case WM_LBUTTONUP:
	{
		//	윈도우화면에서의 해당 좌표
		for (int i = 0; i < 9; i++)
		{
			if (g_isClick[i] == true)
			{
				POINT RealMagnetPos = {
					g_StartPos.x + g_CellSize * g_MagnetPos[i].x,
					g_StartPos.y + g_CellSize * g_MagnetPos[i].y };

				//	sqrt( (x-x0)^2 + (y-y0)^2 )
				float distance = sqrtf(powf(RealMagnetPos.x - g_PiecePos[i].x, 2) + powf(RealMagnetPos.y - g_PiecePos[i].y, 2));

				if (distance < g_CellSize)
				{
					g_PiecePos[i] = RealMagnetPos;
				}
				g_isClick[i] = false;
			}
		}
	}break;
	}
	return WinBase::WndProc(_hWnd, _message, _wParam, _lParam);
}

MyWin::MyWin()
{
}

MyWin::~MyWin()
{
}