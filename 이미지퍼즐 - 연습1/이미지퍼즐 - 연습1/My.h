#pragma once
#include "Global.h"
#include "WinBase.h"
#include "ImgMgr.h"
#include "TimeMgr.h"

class My : public WinBase
{
private:
	//	시작좌표
	POINT m_StartPos = { 400, 100 };
	//	셀의 개수
	SIZE m_Size = { 3, 3 };
	//	셀 한 칸의 크기
	int m_CellSize = 100;
	//	선두께
	int m_LineWidth = 5;
	//	선두께 색상
	COLORREF m_LineColor = RGB(100, 0, 255);
	//	조각사각형의 크기
	POINT m_PiecePos = { 400, 300 };

	//	마그네틱을 위한 좌표
	POINT m_MagnetPos = { 0, 0 };
private:
	VOID Update(float elapseTime);
	VOID Render(HDC hdc);
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	My() = default;
	~My() = default;
};

