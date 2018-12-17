#include "My.h"

VOID My::Update(float elapseTime)
{
	if (GetKeyState(VK_UP) & 0x8000)
	{
		m_PiecePos.y -= 3;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_PiecePos.y += 3;
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_PiecePos.x -= 3;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_PiecePos.x += 3;
	}
}

VOID My::Render(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, m_LineWidth, m_LineColor);
	HPEN hOld = SelectPen(hdc, hPen);

	//	���μ�
	for (long y = 0; y <= m_Size.cy; y++)
	{
		//	���� x ��ǥ + 0, ���� y ��ǥ + �� �� ĭ�� ũ�� * y
		MoveToEx(hdc, m_StartPos.x + 0, m_StartPos.y + m_CellSize * y, nullptr);
		//	���� x ��ǥ + �� �� ĭ�� ũ�� * ������ x ��ǥ, ���� y ��ǥ + �� �� ĭ�� ũ�� * y
		LineTo(hdc, m_StartPos.x + m_CellSize * m_Size.cx, m_StartPos.y + m_CellSize * y);
	}

	//	���μ�
	for (long x = 0; x <= m_Size.cx; x++)
	{
		//	���� x ��ǥ + �� �� ĭ�� ũ�� * x ��ǥ, ���� y ��ǥ + 0
		MoveToEx(hdc, m_StartPos.x + m_CellSize * x, m_StartPos.y + 0, nullptr);
		//	���� x ��ǥ + �� �� ĭ�� ũ��, ���� y ��ǥ + �� �� ĭ�� ũ�� * ������ y ��ǥ
		LineTo(hdc, m_StartPos.x + m_CellSize * x, m_StartPos.y + m_CellSize * m_Size.cy);
	}

	DeleteObject(SelectPen(hdc, hOld));

	RECT rt[9] = { 0, 0, m_CellSize, m_CellSize };

	for (int i = 0; i < 9; i++)
	{
		OffsetRect(&rt[i], m_PiecePos.x, m_PiecePos.y);

		Rectangle(hdc, rt[i].left, rt[i].top, rt[i].right, rt[i].bottom);
	}
	TIME.Render(hdc, 0, 0);
}

LRESULT My::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_SPACE:
				{
					//	������ ȭ�鿡���� �ش� ��ǥ
					POINT RealMagnetPos = { m_StartPos.x + m_CellSize * m_MagnetPos.x, m_StartPos.y + m_CellSize * m_MagnetPos.y };
					

					//	��Ʈ((X - X0)^2 + (Y - Y0)^2)
					float distance = sqrtf(powf((float)RealMagnetPos.x - (float)m_PiecePos.x, 2) + powf((float)RealMagnetPos.y - (float)m_PiecePos.y, 2));

					if (distance <= m_CellSize)
					{
						m_PiecePos.x = RealMagnetPos.x;
						m_PiecePos.y = RealMagnetPos.y;
					}
				}break;
			}
		}break;
	}

	return WinBase::WndProc(hWnd, message, wParam, lParam);
}
