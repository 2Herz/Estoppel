#undef UNICODE
#include "Image.h"

//	Animation Function
void AniInfo::SetFrameTime(initializer_list<float> list)
{
	for (auto &i : list)
	{
		m_frameTime.push_back(i);
	}
}
void AniInfo::Update(float elapseTime)
{
	if (m_isAni == false) return;

	m_time += elapseTime;

	if (m_frameTime[m_nowIndex] <= m_time)
	{
		m_time -= m_frameTime[m_nowIndex];

		m_nowIndex++;

		if (m_nowIndex + 1 == m_frameTime.size())
		{
			if (m_isLoop == false)
			{
				m_isAni = false;
				m_time = 0;
			}
			else
			{
				m_nowIndex = 0;
			}
		}
	}
}
void AniInfo::Start()
{
	m_isAni = true;
	m_nowIndex = 0;
}
void AniInfo::Stop()
{
	m_isAni = false;
	m_nowIndex = 0;
}

//	Image Function
#include <windowsx.h>

Img::Img(HWND hWnd, int width, int height)
{
	CreateImg(hWnd, width, height);
	Clear();
}
Img::Img(HDC hdc, int width, int height)
{
	CreateImg(hdc, width, height);
	Clear();
}
Img::~Img()
{
	DeleteObject(SelectBitmap(ImgDC, OldBit));
	DeleteDC(ImgDC);
}

//	���������Լ�
bool Img::CreateImg(HWND hWnd, int width, int height)
{
	if (hWnd == nullptr || width <= 0 || height <= 0)
	{
		return false;
	}

	HDC hdc = GetDC(hWnd);

	ImgDC = CreateCompatibleDC(hdc);
	Bit = CreateCompatibleBitmap(hdc, width, height);
	OldBit = SelectBitmap(ImgDC, Bit);

	ReleaseDC(hWnd, hdc);

	Size.cx = width;
	Size.cy = height;

	return true;
}
bool Img::CreateImg(HDC hdc, int width, int height)
{
	if (hdc == nullptr || width <= 0 || height <= 0)
	{
		return false;
	}

	ImgDC = CreateCompatibleDC(hdc);
	Bit = CreateCompatibleBitmap(hdc, width, height);
	OldBit = SelectBitmap(ImgDC, Bit);

	Size.cx = width;
	Size.cy = height;

	return true;
}
//	�ҷ�����
bool Img::LoadImg(HWND hWnd, LPCSTR path, int width, int height)
{
	if (hWnd == nullptr || width < 0 || height < 0)
	{
		return false;
	}

	HDC hdc = GetDC(hWnd);

	ImgDC = CreateCompatibleDC(hdc);
	Bit = (HBITMAP)LoadImage(nullptr, path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	OldBit = SelectBitmap(ImgDC, Bit);

	ReleaseDC(hWnd, hdc);

	if (width == 0 && height == 0)
	{
		BITMAP	bm = {};
		GetObject(Bit, sizeof(BITMAP), &bm);

		width = bm.bmWidth;
		height = bm.bmHeight;
	}

	Size.cx = width;
	Size.cy = height;

	IsTrans = FALSE;
	Opacity = 255;

	return true;
}

//	���������Լ�
void Img::SetTrans(BOOL isTrans, COLORREF colorkey)
{
	IsTrans = isTrans;
	Colorkey = colorkey;
}
void Img::SetOpacity(INT opacity)
{
	Opacity = opacity;

	if (Opacity > 255) Opacity = 255;
	if (Opacity < 0) Opacity = 0;
}

//	�����Լ���...
void Img::Render(HDC destDC, int posX, int posY, int width, int height)
{
	if (width == 0 || height == 0)
	{
		width = Size.cx;
		height = Size.cy;
	}

	if (IsTrans == TRUE)
	{
		if (Opacity == 255)
		{
			GdiTransparentBlt(destDC, posX, posY, width, height, ImgDC, 0, 0, Size.cx, Size.cy, Colorkey);
		}
		else
		{
			//	1. �� ���� �����
			Img	epty(destDC, width, height);
			//	2. ����� ����
			BitBlt(epty.GetImgDC(), 0, 0, width, height, destDC, posX, posY, SRCCOPY);
			//	3. �� ���̿� Transp....
			GdiTransparentBlt(epty.GetImgDC(), 0, 0, width, height, ImgDC, 0, 0, Size.cx, Size.cy, Colorkey);

			//	4. ��濡 �����̸� Alpha
			BLENDFUNCTION	bf = {};
			bf.SourceConstantAlpha = Opacity;

			GdiAlphaBlend(destDC, posX, posY, width, height, epty.GetImgDC(), 0, 0, width, height, bf);
		}
	}
	else
	{
		if (Opacity == 255)
		{
			StretchBlt(destDC, posX, posY, width, height, ImgDC, 0, 0, Size.cx, Size.cy, SRCCOPY);
		}
		else
		{
			BLENDFUNCTION	bf = {};
			bf.SourceConstantAlpha = Opacity;

			GdiAlphaBlend(destDC, posX, posY, width, height, ImgDC, 0, 0, Size.cx, Size.cy, bf);
		}
	}
}
void Img::Render(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);

	BitBlt(hdc, 0, 0, Size.cx, Size.cy, ImgDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
}
//	�ִϸ��̼�
void Img::RenderAni(HDC destDC, int frameX, int posX, int posY)
{
	if (IsTrans == TRUE)
	{
		if (Opacity == 255)
		{
			GdiTransparentBlt(destDC, posX, posY, Size.cx, Size.cy, ImgDC, Size.cx * frameX, 0, Size.cx, Size.cy, Colorkey);
		}
		else
		{
			//	1. �� ���� �����
			Img	empty(destDC, Size.cx, Size.cy);
			//	2. ����� ����
			BitBlt(empty.GetImgDC(), 0, 0, Size.cx, Size.cy, destDC, posX, posY, SRCCOPY);
			//	3. �� ���̿� Transp....
			GdiTransparentBlt(empty.GetImgDC(), 0, 0, Size.cx, Size.cy, ImgDC, Size.cx * frameX, 0, Size.cx, Size.cy, Colorkey);

			//	4. ��濡 �����̸� Alpha
			BLENDFUNCTION	bf = {};
			bf.SourceConstantAlpha = Opacity;

			GdiAlphaBlend(destDC, posX, posY, Size.cx, Size.cy, empty.GetImgDC(), 0, 0, Size.cx, Size.cy, bf);
		}
	}
	else
	{
		if (Opacity == 255)
		{
			StretchBlt(destDC, posX, posY, Size.cx, Size.cy, ImgDC, Size.cx * frameX, 0, Size.cx, Size.cy, SRCCOPY);
		}
		else
		{
			BLENDFUNCTION	bf = {};
			bf.SourceConstantAlpha = Opacity;

			GdiAlphaBlend(destDC, posX, posY, Size.cx, Size.cy, ImgDC, Size.cx * frameX, 0, Size.cx, Size.cy, bf);
		}
	}
}
//	�ʽ�ũ��
void Img::RenderScroll(HDC destDC, int posX, int posY, int Offset)
{
	static int offset = 0;

	offset += Offset;

	if (offset > Size.cx)	offset -= Size.cx;
	if (offset < 0)			offset += Size.cx;

	BitBlt(destDC, posX, posY, offset, Size.cy, ImgDC, Size.cx - offset, 0, SRCCOPY);
	BitBlt(destDC, posX + offset, posY, Size.cx - offset, Size.cy, ImgDC, 0, 0, SRCCOPY);
}
//	����
void Img::Clear(COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);

	RECT rc = { 0, 0, Size.cx, Size.cy };
	FillRect(ImgDC, &rc, brush);

	DeleteObject(brush);
}