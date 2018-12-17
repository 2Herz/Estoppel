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
	//	갱신
	VOID	Update(float _elapseTime);
	//	그리기
	VOID	Render(HDC _hdc);
	//	메시지
	LRESULT WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
public:
	MyWin();
	~MyWin();
	
};