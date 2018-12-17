#pragma once
#pragma comment(lib, "msimg32.lib")

#include "Scene.h"

class Scene_Report :
	public Scene
{
private:
	TextUI SaveText;
	BoxUI SaveBox;
	int	m_SaveMenu_Num = 0;
	int	m_SaveMenu_AnswerYes = 0;
	int	m_SaveMenu_AnswerNo = 0;
	int m_SaveMenu_SaveCount = 0;

public:
	Scene_Report();
	~Scene_Report();
	
	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
	
	void Button_Down(int _key);
};

