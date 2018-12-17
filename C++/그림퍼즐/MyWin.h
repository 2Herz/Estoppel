#pragma once

#include "Global.h"
#include "WinBase.h"
#include "TimeMgr.h"
#include "ImgMgr.h"

class MyWin :
	public WinBase
{
private:
	POINT		m_MousePos = {};
	POINT		g_StartPos = { 600, 200 };
	SIZE		g_Size = { 3, 3 };
	int			g_CellSize = 100;
	int			g_LineWidth = 1;
	COLORREF	g_LineColor = RGB(0, 0, 255);

	//	마그네틱을 예제를 위한 좌표
	POINT		g_PiecePos[10] = {	{  50,  90 },{ 160,  90 },{ 270,  90 },
									{  50, 200 },{ 160, 200 },{ 270, 200 },
									{  50, 310 },{ 160, 310 },{ 270, 310 },
									{ 380, 420 } };

	POINT		g_MagnetPos[9] = {	{ 0, 0 },{ 1, 0 },{ 2, 0 },
									{ 0, 1 },{ 1, 1 },{ 2, 1 },
									{ 0, 2 },{ 1, 2 },{ 2, 2 } };
	bool		g_isClick[9] = {};
	float		g_CheckPosX = 0;
	float		g_CheckPosY = 0;
private:
	//	Init
	VOID	Init(HWND _hWnd);
	//	Release
	VOID	Release();
	//	갱신
	VOID	Update(float _elapseTime);
	//	그리기
	VOID	Render(HDC _hdc);
	//	메시지
	LRESULT WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
public:
	MyWin();
	~MyWin();
	
};