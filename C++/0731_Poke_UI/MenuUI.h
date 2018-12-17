#pragma once

#include "Global.h"

#include "DictionaryUI.h"
#include "PokemonUI.h"
#include "SaveUI.h"
#include "SettingMenuUI.h"

class MenuUI
{
private:
	BoxUI			m_Box;
	TextUI			m_Txt;
	DictionaryUI	m_Dic;
	PokemonUI		m_PokemonUI;
	SaveUI			m_Save;
	SettingMenuUI	m_Setting;

public:
	bool	m_isClick = false;
	int		m_Select = 0;
public:
	MenuUI();
	~MenuUI();
	void	Init(HWND _hWnd);
	void	RenderMenu(HDC _hdc);
};

