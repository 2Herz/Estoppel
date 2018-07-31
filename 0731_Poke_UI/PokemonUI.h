#pragma once

#include "Global.h"

class PokemonUI
{
private:
	int		m_PokemonCount	= 4;		//	���ϰ� �ִ� ���ϸ� (1 ~ 6)
	int		m_PokemonSelect		= 0;
	bool	m_isBattle		= false;
	bool	m_isClick		= false;
	HDC		m_BGDC			= nullptr;
	BoxUI	m_Box;
	TextUI	m_Txt;
	//pokemonData

public:
	PokemonUI();
	~PokemonUI();

	void	Init(HWND _hWnd);
	void	RenderPokemon(HDC _hdc);
};