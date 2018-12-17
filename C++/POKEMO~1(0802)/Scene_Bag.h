#pragma once
#include "Scene.h"

class Scene_Bag :
	public Scene
{
private:
	HDC		m_BGDC = nullptr;
	BoxUI	m_Box;
	TextUI	m_Txt;
	//AniInfo	m_Ani;
	int		m_Ani = 0;
	float	m_time = 0;
public:
	int		m_BagNum = 0;
public:
	Scene_Bag();
	~Scene_Bag();
	
	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};

