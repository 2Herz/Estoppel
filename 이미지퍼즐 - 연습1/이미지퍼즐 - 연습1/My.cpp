#include "My.h"

VOID My::Update(float elapseTime)
{
	Piece pie;

	if (GetKeyState(VK_UP) & 0x8000)
	{
		//	Ã¹¹øÂ° »ç°¢Çü
		if (pie.m_PiecePos[0].y)
		{
			pie.m_PiecePos[0].y -= 3;
		}

		else if (pie.m_PiecePos[1].y)
		{
			pie.m_PiecePos[1].y -= 3;
		}
		else if (pie.m_PiecePos[2].y)
		{
			pie.m_PiecePos[2].y -= 3;
		}
		else if (pie.m_PiecePos[3].y)
		{
			pie.m_PiecePos[3].y -= 3;
		}
		else if (pie.m_PiecePos[4].y)
		{
			pie.m_PiecePos[4].y -= 3;
		}
		else if (pie.m_PiecePos[5].y)
		{
			pie.m_PiecePos[5].y -= 3;
		}
		else if (pie.m_PiecePos[6].y)
		{
			pie.m_PiecePos[6].y -= 3;
		}
		else if (pie.m_PiecePos[7].y)
		{
			pie.m_PiecePos[7].y -= 3;
		}
		else if (pie.m_PiecePos[8].y)
		{
			pie.m_PiecePos[8].y -= 3;
		}
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		if (pie.m_PiecePos[0].y)
		{
			pie.m_PiecePos[0].y += 3;
		}

		else if (pie.m_PiecePos[1].y)
		{
			pie.m_PiecePos[1].y += 3;
		}
		else if (pie.m_PiecePos[2].y)
		{
			pie.m_PiecePos[2].y += 3;
		}
		else if (pie.m_PiecePos[3].y)
		{
			pie.m_PiecePos[3].y += 3;
		}
		else if (pie.m_PiecePos[4].y)
		{
			pie.m_PiecePos[4].y += 3;
		}
		else if (pie.m_PiecePos[5].y)
		{
			pie.m_PiecePos[5].y += 3;
		}
		else if (pie.m_PiecePos[6].y)
		{
			pie.m_PiecePos[6].y += 3;
		}
		else if (pie.m_PiecePos[7].y)
		{
			pie.m_PiecePos[7].y += 3;
		}
		else if (pie.m_PiecePos[8].y)
		{
			pie.m_PiecePos[8].y += 3;
		}
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		if (pie.m_PiecePos[0].x)
		{
			pie.m_PiecePos[0].x -= 3;
		}

		else if (pie.m_PiecePos[1].x)
		{
			pie.m_PiecePos[1].x -= 3;
		}
		else if (pie.m_PiecePos[2].x)
		{
			pie.m_PiecePos[2].x -= 3;
		}
		else if (pie.m_PiecePos[3].x)
		{
			pie.m_PiecePos[3].x -= 3;
		}
		else if (pie.m_PiecePos[4].x)
		{
			pie.m_PiecePos[4].x -= 3;
		}
		else if (pie.m_PiecePos[5].x)
		{
			pie.m_PiecePos[5].x -= 3;
		}
		else if (pie.m_PiecePos[6].x)
		{
			pie.m_PiecePos[6].x -= 3;
		}
		else if (pie.m_PiecePos[7].x)
		{
			pie.m_PiecePos[7].x -= 3;
		}
		else if (pie.m_PiecePos[8].x)
		{
			pie.m_PiecePos[8].x -= 3;
		}
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		if (pie.m_PiecePos[0].x)
		{
			pie.m_PiecePos[0].x += 3;
		}

		else if (pie.m_PiecePos[1].x)
		{
			pie.m_PiecePos[1].x += 3;
		}
		else if (pie.m_PiecePos[2].x)
		{
			pie.m_PiecePos[2].x += 3;
		}
		else if (pie.m_PiecePos[3].x)
		{
			pie.m_PiecePos[3].x += 3;
		}
		else if (pie.m_PiecePos[4].x)
		{
			pie.m_PiecePos[4].x += 3;
		}
		else if (pie.m_PiecePos[5].x)
		{
			pie.m_PiecePos[5].x += 3;
		}
		else if (pie.m_PiecePos[6].x)
		{
			pie.m_PiecePos[6].x += 3;
		}
		else if (pie.m_PiecePos[7].x)
		{
			pie.m_PiecePos[7].x += 3;
		}
		else if (pie.m_PiecePos[8].x)
		{
			pie.m_PiecePos[8].x += 3;
		}
	}

	/*if (GetKeyState(VK_UP) & 0x8000)
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
	}*/
}

VOID My::Render(HDC hdc)
{
	Magnet mag;
	Piece pie;

	HPEN hPen = CreatePen(PS_SOLID, m_LineWidth, m_LineColor);
	HPEN hOld = SelectPen(hdc, hPen);

	//	°¡·Î¼±
	for (long y = 0; y <= m_Size.cy; y++)
	{
		//	½ÃÀÛ x ÁÂÇ¥ + 0, ½ÃÀÛ y ÁÂÇ¥ + ¼¿ ÇÑ Ä­ÀÇ Å©±â * y
		MoveToEx(hdc, m_StartPos.x + 0, m_StartPos.y + m_CellSize * y, nullptr);
		//	½ÃÀÛ x ÁÂÇ¥ + ¼¿ ÇÑ Ä­ÀÇ Å©±â * »çÀÌÁî x ÁÂÇ¥, ½ÃÀÛ y ÁÂÇ¥ + ¼¿ ÇÑ Ä­ÀÇ Å©±â * y
		LineTo(hdc, m_StartPos.x + m_CellSize * m_Size.cx, m_StartPos.y + m_CellSize * y);
	}

	//	¼¼·Î¼±
	for (long x = 0; x <= m_Size.cx; x++)
	{
		//	½ÃÀÛ x ÁÂÇ¥ + ¼¿ ÇÑ Ä­ÀÇ Å©±â * x ÁÂÇ¥, ½ÃÀÛ y ÁÂÇ¥ + 0
		MoveToEx(hdc, m_StartPos.x + m_CellSize * x, m_StartPos.y + 0, nullptr);
		//	½ÃÀÛ x ÁÂÇ¥ + ¼¿ ÇÑ Ä­ÀÇ Å©±â, ½ÃÀÛ y ÁÂÇ¥ + ¼¿ ÇÑ Ä­ÀÇ Å©±â * »çÀÌÁî y ÁÂÇ¥
		LineTo(hdc, m_StartPos.x + m_CellSize * x, m_StartPos.y + m_CellSize * m_Size.cy);
	}

	DeleteObject(SelectPen(hdc, hOld));

	RECT rt = { 0, 0, m_CellSize, m_CellSize };

	OffsetRect(&rt, pie.m_PiecePos[0].x, pie.m_PiecePos[0].y);

	Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);

	TIME.Render(hdc, 0, 0);
}

LRESULT My::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Magnet mag;
	Piece pie;

	for (int i = 0; i < 10; i++)
	{
		mag.m_MagnetPos[i] = { i, i };
	}

	switch (message)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_SPACE:
				{
					//	À©µµ¿ì È­¸é¿¡¼­ÀÇ ÇØ´ç ÁÂÇ¥
					POINT RealMagnetPos = { m_StartPos.x + m_CellSize * mag.m_MagnetPos[0].x, m_StartPos.y + m_CellSize * mag.m_MagnetPos[0].y };
					POINT RealMagnetPos1 = { m_StartPos.x + m_CellSize * mag.m_MagnetPos[1].x, m_StartPos.y + m_CellSize * mag.m_MagnetPos[1].y };
					POINT RealMagnetPos2 = { m_StartPos.x + m_CellSize * mag.m_MagnetPos[2].x, m_StartPos.y + m_CellSize * mag.m_MagnetPos[2].y };
					POINT RealMagnetPos3 = { m_StartPos.x + m_CellSize * mag.m_MagnetPos[3].x, m_StartPos.y + m_CellSize * mag.m_MagnetPos[3].y };
					POINT RealMagnetPos4 = { m_StartPos.x + m_CellSize * mag.m_MagnetPos[4].x, m_StartPos.y + m_CellSize * mag.m_MagnetPos[4].y };
					POINT RealMagnetPos5 = { m_StartPos.x + m_CellSize * mag.m_MagnetPos[5].x, m_StartPos.y + m_CellSize * mag.m_MagnetPos[5].y };
					POINT RealMagnetPos6 = { m_StartPos.x + m_CellSize * mag.m_MagnetPos[6].x, m_StartPos.y + m_CellSize * mag.m_MagnetPos[6].y };
					POINT RealMagnetPos7 = { m_StartPos.x + m_CellSize * mag.m_MagnetPos[7].x, m_StartPos.y + m_CellSize * mag.m_MagnetPos[7].y };
					POINT RealMagnetPos8 = { m_StartPos.x + m_CellSize * mag.m_MagnetPos[8].x, m_StartPos.y + m_CellSize * mag.m_MagnetPos[8].y };

					//	·çÆ®((X - X0)^2 + (Y - Y0)^2)
					float distance = sqrtf(powf((float)RealMagnetPos.x - (float)pie.m_PiecePos[0].x, 2) + powf((float)RealMagnetPos.y - (float)pie.m_PiecePos[0].y, 2));
					float distance1 = sqrtf(powf((float)RealMagnetPos1.x - (float)pie.m_PiecePos[1].x, 2) + powf((float)RealMagnetPos1.y - (float)pie.m_PiecePos[1].y, 2));
					float distance2 = sqrtf(powf((float)RealMagnetPos2.x - (float)pie.m_PiecePos[2].x, 2) + powf((float)RealMagnetPos2.y - (float)pie.m_PiecePos[2].y, 2));
					float distance3 = sqrtf(powf((float)RealMagnetPos3.x - (float)pie.m_PiecePos[3].x, 2) + powf((float)RealMagnetPos3.y - (float)pie.m_PiecePos[3].y, 2));
					float distance4 = sqrtf(powf((float)RealMagnetPos4.x - (float)pie.m_PiecePos[4].x, 2) + powf((float)RealMagnetPos4.y - (float)pie.m_PiecePos[4].y, 2));
					float distance5 = sqrtf(powf((float)RealMagnetPos5.x - (float)pie.m_PiecePos[5].x, 2) + powf((float)RealMagnetPos5.y - (float)pie.m_PiecePos[5].y, 2));
					float distance6 = sqrtf(powf((float)RealMagnetPos6.x - (float)pie.m_PiecePos[6].x, 2) + powf((float)RealMagnetPos6.y - (float)pie.m_PiecePos[6].y, 2));
					float distance7 = sqrtf(powf((float)RealMagnetPos7.x - (float)pie.m_PiecePos[7].x, 2) + powf((float)RealMagnetPos7.y - (float)pie.m_PiecePos[7].y, 2));
					float distance8 = sqrtf(powf((float)RealMagnetPos8.x - (float)pie.m_PiecePos[8].x, 2) + powf((float)RealMagnetPos8.y - (float)pie.m_PiecePos[8].y, 2));


					if (distance <= m_CellSize)
					{
						pie.m_PiecePos[0].x = RealMagnetPos.x;
						pie.m_PiecePos[0].y = RealMagnetPos.y;
					}
					else if (distance <= m_CellSize)
					{
						pie.m_PiecePos[1].x = RealMagnetPos1.x;
						pie.m_PiecePos[1].y = RealMagnetPos1.y;
					}
					else if (distance <= m_CellSize)
					{
						pie.m_PiecePos[2].x = RealMagnetPos2.x;
						pie.m_PiecePos[2].y = RealMagnetPos2.y;
					}
					else if (distance <= m_CellSize)
					{
						pie.m_PiecePos[3].x = RealMagnetPos3.x;
						pie.m_PiecePos[3].y = RealMagnetPos3.y;
					}
					else if (distance <= m_CellSize)
					{
						pie.m_PiecePos[4].x = RealMagnetPos4.x;
						pie.m_PiecePos[4].y = RealMagnetPos4.y;
					}
					else if (distance <= m_CellSize)
					{
						pie.m_PiecePos[5].x = RealMagnetPos5.x;
						pie.m_PiecePos[5].y = RealMagnetPos5.y;
					}
					else if (distance <= m_CellSize)
					{
						pie.m_PiecePos[6].x = RealMagnetPos6.x;
						pie.m_PiecePos[6].y = RealMagnetPos6.y;
					}
					else if (distance <= m_CellSize)
					{
						pie.m_PiecePos[7].x = RealMagnetPos7.x;
						pie.m_PiecePos[7].y = RealMagnetPos7.y;
					}
					else if (distance <= m_CellSize)
					{
						pie.m_PiecePos[8].x = RealMagnetPos8.x;
						pie.m_PiecePos[8].y = RealMagnetPos8.y;
					}
				}break;
			}
		}break;
	}

	return WinBase::WndProc(hWnd, message, wParam, lParam);
}
