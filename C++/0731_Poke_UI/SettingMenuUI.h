#pragma once
#include "Global.h"

class SettingMenuUI
{
private:
	TextUI		SettingMenuText;
	BoxUI		SettingMenuBox;
	int			m_SettingMenu_Num = 0;
	int			m_SettingMenu_TextSpeed = 0;
	int			m_SettingMenu_BattleScene = 0;
	int			m_SettingMenu_BattleStyle = 0;
	int			m_SettingMenu_Sound = 0;
	int			m_SettingMenu_ButtonMode = 0;
	int			m_SettingMenu_Frame = 0;

public:
	void	Init(HWND _hWnd);
	void Click_Button(int _key);
	void MenuDisplay(HDC _hdc);
	int  Getm_SettingMenu_TextSpeed()
	{
		return m_SettingMenu_TextSpeed;
	}
	int  Getm_SettingMenu_BattleScene()
	{
		return m_SettingMenu_BattleScene;
	}
	int  Getm_SettingMenu_BattleStyle()
	{
		return m_SettingMenu_BattleStyle;
	}
	int  Getm_SettingMenu_Sound()
	{
		return m_SettingMenu_Sound;
	}
	int  Getm_SettingMenu_ButtonMode()
	{
		return m_SettingMenu_ButtonMode;
	}
	int  Getm_SettingMenu_Frame()
	{
		return m_SettingMenu_Frame;
	}
	SettingMenuUI();
	~SettingMenuUI();
};

