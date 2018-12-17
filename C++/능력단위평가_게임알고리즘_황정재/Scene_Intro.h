#pragma once
#include "Scene.h"
#include "FPOINT.h"
#include <vector>
#include "Monster.h"

class Scene_Intro :
	public Scene
{
	Monster m_monster;
public:
	Scene_Intro();
	~Scene_Intro();

	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};