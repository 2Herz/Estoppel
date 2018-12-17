#pragma once
#include "Scene.h"

class Scene_Battle :
	public Scene
{
private:
	HDC		m_BGDC = nullptr;
	HDC		m_BGDC1 = nullptr;
	BoxUI	m_Box;
	TextUI	m_Txt;

public:
	Scene_Battle();
	~Scene_Battle();

	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};

