#pragma once
#include "Global.h"
#include "Base.h"
#include "ImageManager.h"
#include "TimeManager.h"

class My : public Base
{
private:
	bool	isFocus = true;
	POINT	MousePos = {};
	POINT	StartTilePos = { 0, 0 };
	SIZE	SellSize = {};
	INT		nx = 0;
	INT		ny = 0;

private:
	VOID Init(HWND hWnd);
	VOID Release();
	VOID Update(float elapseTime);
	VOID Render(HDC hdc);
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	My();
	~My();
};