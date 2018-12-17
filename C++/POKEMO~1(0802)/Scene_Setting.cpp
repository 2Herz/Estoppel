#include "stdafx.h"
#include "Scene_Setting.h"
#include "SceneMgr.h"

void Scene_Setting::Init(HWND _hWnd)
{
	/*IMG_MGR->OpenImg("Images/UI/SettingMenu.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuSBOX.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack0.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack1.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack2.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack3.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack4.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack5.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack6.bmp");*/
}

void Scene_Setting::Update(float _elapseTime)
{
}

void Scene_Setting::Render(HDC _hdc)
{
	IMG_MGR->GetImg("SettingMenu")->Render(_hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT);
	IMG_MGR->GetImg("SettingMenuSBOX")->Render(_hdc, 40, 72);

	SettingMenuText.TextBox(_hdc, 96, 100, "���ϸ���  ���̾��  ȯ�漳��", 50, GRAY);
	SettingMenuBox.BoxCreate(_hdc, 1, 6, 28, 19);


	SettingMenuText.TextBox(_hdc, 96, 240, "�̾߱���  �ӵ�", 50, GRAY);
	SettingMenuText.TextBox(_hdc, 96, 290, "���� �ִϸ��̼�", 50, GRAY);
	SettingMenuText.TextBox(_hdc, 96, 340, "������  ��", 50, GRAY);
	SettingMenuText.TextBox(_hdc, 96, 390, "����", 50, GRAY);
	SettingMenuText.TextBox(_hdc, 96, 440, "��ư  ���", 50, GRAY);
	SettingMenuText.TextBox(_hdc, 96, 490, "������", 50, GRAY);
	SettingMenuText.TextBox(_hdc, 96, 540, "����", 50, GRAY);

	if (m_SettingMenu_TextSpeed == 0)
	{
		SettingMenuText.TextBox(_hdc, 576, 240, "����", 50, LORANGE, ORANGE);
	}
	else if (m_SettingMenu_TextSpeed == 1)
	{
		SettingMenuText.TextBox(_hdc, 576, 240, "������", 50, LORANGE, ORANGE);
	}
	else if (m_SettingMenu_TextSpeed == 2)
	{
		SettingMenuText.TextBox(_hdc, 576, 240, "������", 50, LORANGE, ORANGE);
	}

	if (m_SettingMenu_BattleScene == 0)
	{
		SettingMenuText.TextBox(_hdc, 576, 290, "����", 50, LORANGE, ORANGE);
	}
	else if (m_SettingMenu_BattleScene == 1)
	{
		SettingMenuText.TextBox(_hdc, 576, 290, "�����ʴ´�", 50, LORANGE, ORANGE);
	}

	if (m_SettingMenu_BattleStyle == 0)
	{
		SettingMenuText.TextBox(_hdc, 576, 340, "��ü", 50, LORANGE, ORANGE);
	}
	else if (m_SettingMenu_BattleStyle == 1)
	{
		SettingMenuText.TextBox(_hdc, 576, 340, "��ʸ�Ʈ", 50, LORANGE, ORANGE);
	}

	if (m_SettingMenu_Sound == 0)
	{
		SettingMenuText.TextBox(_hdc, 576, 390, "���", 50, LORANGE, ORANGE);
	}
	else if (m_SettingMenu_Sound == 1)
	{
		SettingMenuText.TextBox(_hdc, 576, 390, "���׷���", 50, LORANGE, ORANGE);
	}

	if (m_SettingMenu_ButtonMode == 0)
	{
		SettingMenuText.TextBox(_hdc, 576, 440, "�븻", 50, LORANGE, ORANGE);
	}
	else if (m_SettingMenu_ButtonMode == 1)
	{
		SettingMenuText.TextBox(_hdc, 576, 440, "LR", 50, LORANGE, ORANGE);
	}
	else if (m_SettingMenu_ButtonMode == 2)
	{
		SettingMenuText.TextBox(_hdc, 576, 440, "L�� A��", 50, LORANGE, ORANGE);
	}

	if (m_SettingMenu_Frame == 0)
	{
		SettingMenuText.TextBox(_hdc, 576, 490, "Ÿ��  1", 50, LORANGE, ORANGE);
	}
	else if (m_SettingMenu_Frame == 1)
	{
		SettingMenuText.TextBox(_hdc, 576, 490, "Ÿ��  2", 50, LORANGE, ORANGE);
	}
	else if (m_SettingMenu_Frame == 2)
	{
		SettingMenuText.TextBox(_hdc, 576, 490, "Ÿ��  3", 50, LORANGE, ORANGE);
	}
	else if (m_SettingMenu_Frame == 3)
	{
		SettingMenuText.TextBox(_hdc, 576, 490, "Ÿ��  4", 50, LORANGE, ORANGE);
	}
	else if (m_SettingMenu_Frame == 4)
	{
		SettingMenuText.TextBox(_hdc, 576, 490, "Ÿ��  5", 50, LORANGE, ORANGE);
	}


	IMG_MGR->GetImg("SettingMenuBlack")->Render(_hdc, 64, 230, 832, 10);
	IMG_MGR->GetImg("SettingMenuBlack0")->Render(_hdc, 64, 240, 832, 50);
	IMG_MGR->GetImg("SettingMenuBlack1")->Render(_hdc, 64, 290, 832, 50);
	IMG_MGR->GetImg("SettingMenuBlack2")->Render(_hdc, 64, 340, 832, 50);
	IMG_MGR->GetImg("SettingMenuBlack3")->Render(_hdc, 64, 390, 832, 50);
	IMG_MGR->GetImg("SettingMenuBlack4")->Render(_hdc, 64, 440, 832, 50);
	IMG_MGR->GetImg("SettingMenuBlack5")->Render(_hdc, 64, 490, 832, 50);
	IMG_MGR->GetImg("SettingMenuBlack6")->Render(_hdc, 64, 540, 832, 50);
	IMG_MGR->GetImg("SettingMenuBlack")->Render(_hdc, 64, 590, 832, 10);

	IMG_MGR->GetImg("SettingMenuBlack")->SetOpacity(50);

	if (m_SettingMenu_Num == 0)
	{
		IMG_MGR->GetImg("SettingMenuBlack0")->SetOpacity(0);
	}
	else
	{
		IMG_MGR->GetImg("SettingMenuBlack0")->SetOpacity(50);
	}

	if (m_SettingMenu_Num == 1)
	{
		IMG_MGR->GetImg("SettingMenuBlack1")->SetOpacity(0);
	}
	else
	{
		IMG_MGR->GetImg("SettingMenuBlack1")->SetOpacity(50);
	}

	if (m_SettingMenu_Num == 2)
	{
		IMG_MGR->GetImg("SettingMenuBlack2")->SetOpacity(0);
	}
	else
	{
		IMG_MGR->GetImg("SettingMenuBlack2")->SetOpacity(50);
	}

	if (m_SettingMenu_Num == 3)
	{
		IMG_MGR->GetImg("SettingMenuBlack3")->SetOpacity(0);
	}
	else
	{
		IMG_MGR->GetImg("SettingMenuBlack3")->SetOpacity(50);
	}

	if (m_SettingMenu_Num == 4)
	{
		IMG_MGR->GetImg("SettingMenuBlack4")->SetOpacity(0);
	}
	else
	{
		IMG_MGR->GetImg("SettingMenuBlack4")->SetOpacity(50);
	}

	if (m_SettingMenu_Num == 5)
	{
		IMG_MGR->GetImg("SettingMenuBlack5")->SetOpacity(0);
	}
	else
	{
		IMG_MGR->GetImg("SettingMenuBlack5")->SetOpacity(50);
	}

	if (m_SettingMenu_Num == 6)
	{
		IMG_MGR->GetImg("SettingMenuBlack6")->SetOpacity(0);
	}
	else
	{
		IMG_MGR->GetImg("SettingMenuBlack6")->SetOpacity(50);
	}
}

void Scene_Setting::Click_Button(int _key)
{
	if (VK_LEFT == _key)
	{
		if (m_SettingMenu_Num == 0)
		{
			m_SettingMenu_TextSpeed--;
			if (m_SettingMenu_TextSpeed < 0)
				m_SettingMenu_TextSpeed = 2;
		}
		else if (m_SettingMenu_Num == 1)
		{
			m_SettingMenu_BattleScene--;
			if (m_SettingMenu_BattleScene < 0)
				m_SettingMenu_BattleScene = 1;
		}
		else if (m_SettingMenu_Num == 2)
		{
			m_SettingMenu_BattleStyle--;
			if (m_SettingMenu_BattleStyle < 0)
				m_SettingMenu_BattleStyle = 1;
		}
		else if (m_SettingMenu_Num == 3)
		{
			m_SettingMenu_Sound--;
			if (m_SettingMenu_Sound < 0)
				m_SettingMenu_Sound = 1;
		}
		else if (m_SettingMenu_Num == 4)
		{
			m_SettingMenu_ButtonMode--;
			if (m_SettingMenu_ButtonMode < 0)
				m_SettingMenu_ButtonMode = 2;
		}
		else if (m_SettingMenu_Num == 5)
		{
			m_SettingMenu_Frame--;
			if (m_SettingMenu_Frame < 0)
				m_SettingMenu_Frame = 4;
		}

	}
	if (VK_RIGHT == _key)
	{
		if (m_SettingMenu_Num == 0)
		{
			m_SettingMenu_TextSpeed++;
			if (m_SettingMenu_TextSpeed > 2)
				m_SettingMenu_TextSpeed = 0;
		}
		else if (m_SettingMenu_Num == 1)
		{
			m_SettingMenu_BattleScene++;
			if (m_SettingMenu_BattleScene > 1)
				m_SettingMenu_BattleScene = 0;
		}
		else if (m_SettingMenu_Num == 2)
		{
			m_SettingMenu_BattleStyle++;
			if (m_SettingMenu_BattleStyle > 1)
				m_SettingMenu_BattleStyle = 0;
		}
		else if (m_SettingMenu_Num == 3)
		{
			m_SettingMenu_Sound++;
			if (m_SettingMenu_Sound > 1)
				m_SettingMenu_Sound = 0;
		}
		else if (m_SettingMenu_Num == 4)
		{
			m_SettingMenu_ButtonMode++;
			if (m_SettingMenu_ButtonMode > 2)
				m_SettingMenu_ButtonMode = 0;
		}
		else if (m_SettingMenu_Num == 5)
		{
			m_SettingMenu_Frame++;
			if (m_SettingMenu_Frame > 4)
				m_SettingMenu_Frame = 0;
		}


	}
	if (VK_UP == _key)
	{
		m_SettingMenu_Num--;
		if (m_SettingMenu_Num < 0)
		{
			m_SettingMenu_Num = 6;
		}

	}
	if (VK_DOWN == _key)
	{
		m_SettingMenu_Num++;
		if (m_SettingMenu_Num > 6)
		{
			m_SettingMenu_Num = 0;
		}
	}
}

Scene_Setting::Scene_Setting()
{
}


Scene_Setting::~Scene_Setting()
{
}

bool Scene_Setting::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case 'x':
		case 'X': {	SCENE_MGR.SetScene(SCENE_MENU); }break;

		case VK_ESCAPE: return true;	break;
		}
	}break;

	}
	return false;
}