#pragma once
#include "Scene.h"

class Scene_Pokemon :
	public Scene
{
private:
	int		m_PokemonCount	= 4;		//	지니고 있는 포켓몬 (1 ~ 6)
	int		m_PokemonSelect	= 0;
	bool	m_isBattle		= false;
	bool	m_isClick		= false;
	HDC		m_BGDC			= nullptr;
	BoxUI	m_Box;
	TextUI	m_Txt;
	//pokemonData

public:
	Scene_Pokemon();
	~Scene_Pokemon();

	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};