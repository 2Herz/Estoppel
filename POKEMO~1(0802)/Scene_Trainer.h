#pragma once
#include "Scene.h"

class Scene_Trainer :
	public Scene
{
public:
	Scene_Trainer();
	~Scene_Trainer();

	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};

