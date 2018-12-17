#pragma once
#include "Scene.h"

class Scene_Main :
	public Scene
{
public:
	Scene_Main();
	~Scene_Main();

	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};

