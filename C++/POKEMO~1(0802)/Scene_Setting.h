#pragma once
#include "Scene.h"

class Scene_Setting :
	public Scene
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
	Scene_Setting();
	~Scene_Setting();

	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	void Click_Button(int _key);
	
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
};

