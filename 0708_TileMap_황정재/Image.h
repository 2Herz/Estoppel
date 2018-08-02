#pragma once

#include <Windows.h>
#include <vector>
#include <initializer_list>
using namespace std;

class AniInfo
{
	float m_time = 0;
	vector<float> m_frameTime;

public:
	bool m_isAni = false;
	int m_nowIndex = 0;
	bool m_isLoop = false;

	void SetFrameTime(initializer_list<float> list);
	void Update(float elapseTime);
	void Start();
	void Stop();
};

class Img
{
private:
	HDC			ImgDC;
	HBITMAP		Bit, OldBit;
	SIZE		Size;
	BOOL		IsTrans;
	COLORREF	Colorkey;
	INT			Opacity;

public:
	Img() = default;
	Img(HWND hWnd, int width, int height);
	Img(HDC hdc, int width, int height);
	~Img();

	//	����
	bool	CreateImg(HWND hWnd, int width, int height);
	bool	CreateImg(HDC hdc, int width, int height);
	bool	LoadImg(HWND hWnd, LPCSTR path, int width = 0, int height = 0);

	//	����
	void SetTrans(BOOL isTrans = TRUE, COLORREF colorkey = RGB(255, 0, 255));
	void SetOpacity(INT opacity);
	INT GetOpacity()
	{
		return Opacity;
	}
	void SetFrame(int frame)
	{
		Size.cx /= frame;
	}

	//	����
	void Render(HDC destDC, int posX = 0, int posY = 0, int width = 0, int height = 0);
	void Render(HWND hWnd);

	//	�ִϸ��̼�
	void RenderAni(HDC destDC, int frameX, int posX = 0, int posY = 0);

	//	��ũ��
	void RenderScroll(HDC destDC, int posX, int posY, int Offset);

	//	����
	void Clear(COLORREF color = RGB(255, 255, 255));

	//	������
	HDC GetImgDC()
	{
		return ImgDC;
	}
	SIZE GetSize()
	{
		return Size;
	}
};