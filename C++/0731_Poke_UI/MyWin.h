#pragma once

#include "Global.h"
#include "WinBase.h"

#include "MenuUI.h"

#include "DictionaryUI.h"
#include "PokemonUI.h"
#include "SaveUI.h"
#include "SettingMenuUI.h"

class MyWin :
	public WinBase
{
private:
	POINT		m_MousePos = {};
	TextUI		txt;
	BoxUI		box;
	PokemonUI	pokemonUI;
	MenuUI		menuUI;
private:
	//	Init
	VOID	Init(HWND _hWnd);
	//	Release
	VOID	Release();
	//	����
	VOID	Update(float _elapseTime);
	//	�׸���
	VOID	Render(HDC _hdc);
	//	�޽���
	LRESULT WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
public:
	MyWin();
	~MyWin();
	
};