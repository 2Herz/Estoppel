#pragma once
#include "Global.h"
#include "WinBase.h"
#include "ImgMgr.h"
#include "TimeMgr.h"

class My : public WinBase
{
private:
	//	������ǥ
	POINT m_StartPos = { 100, 100 };
	//	���� ����
	SIZE m_Size = { 3, 3 };
	//	�� �� ĭ�� ũ��
	int m_CellSize = 100;
	//	���β�
	int m_LineWidth = 5;
	//	���β� ����
	COLORREF m_LineColor = RGB(100, 0, 255);
	//	�����簢���� ũ��
	struct Piece
	{
		POINT m_PiecePos[9] = { 400, 300 };
	};
	//	���׳�ƽ�� ���� ��ǥ
	struct Magnet
	{
		POINT m_MagnetPos[9] = {};
	};
private:
	VOID Update(float elapseTime);
	VOID Render(HDC hdc);
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	My() = default;
	~My() = default;
};

