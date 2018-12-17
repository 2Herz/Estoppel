#pragma once
#include "Scene.h"

class Scene_Main :
	public Scene
{
public:
	float m_time = 0.0f;
	bool m_isGridMode = false;
	std::stringstream m_posStr;
	POINT m_mousePos;
	bool m_rideBike = false;

	HDC m_screen;

public:
	Scene_Main();
	~Scene_Main();

	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};

