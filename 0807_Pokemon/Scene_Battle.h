#pragma once
#include "Scene.h"
#include <vector>

enum BATTLE_TYPE
{
	INTRO,
	BATTLE,
	REACTION,
	CHANGE,
	ENDBATTLE
};
enum REACTION_TYPE
{
	REACTION_CRITICAL,
	REACTION_GOOD,
	REACTION_NORMAL,
	REACTION_BAD,
	REACTION_NO
};

class Scene_Battle :
	public Scene
{
private:
	HDC				m_BGDC = nullptr;
	HDC				m_BGDC1 = nullptr;
	BoxUI			m_Box;
	TextUI			m_Txt;
	int		i = 0;
	int				m_EnemyMove = -512;
	int				m_EnemyInfo = -400;
	int				m_MyMove	= 960;
	int				m_Ani = 0;
	int				m_playerAni = 0;
	int				m_ballAni = 0;
	int				m_playerExit = 0;
	float			m_time = 0;
	float			m_ballTime = 0;

public:
	BATTLE_TYPE		m_Type		= INTRO;
	REACTION_TYPE	m_Reaction	= REACTION_NORMAL;

public:
	Scene_Battle();
	~Scene_Battle();

	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};

