#include "stdafx.h"
#include "Scene_Report.h"
#include "SceneMgr.h"


Scene_Report::Scene_Report()
{
}
Scene_Report::~Scene_Report()
{
}

void Scene_Report::Init(HWND _hWnd)
{
	/*IMG_MGR->OpenImg("Images/UI/SaveBox1.bmp");
	IMG_MGR->OpenImg("Images/UI/SaveBox2.bmp");
	IMG_MGR->OpenImg("Images/UI/SaveBox3.bmp");*/
}

void Scene_Report::Update(float _elapseTime)
{
}

void Scene_Report::Render(HDC _hdc)
{
	IMG_MGR->GetImg("SaveBox1")->Render(_hdc, 20, 460, 920, 170);
	IMG_MGR->GetImg("SaveBox3")->Render(_hdc, 10, 20, 500, 340);

	SaveText.TextBox(_hdc, 30, 110, "���ΰ�", 35, GRAY);
	SaveText.TextBox(_hdc, 30, 170, "���� ����", 35, GRAY);
	SaveText.TextBox(_hdc, 30, 230, "���ϸ� ����", 35, GRAY);
	SaveText.TextBox(_hdc, 30, 290, "�÷��� �ð�", 35, GRAY);

	// �ٲ� �κ�
	SaveText.TextBox(_hdc, 172, 52, "��Ƽ�̸�", 45, BLUE, LBLUE);
	SaveText.TextBox(_hdc, 260, 110, "�г���", 40, GRAY, LGRAY);
	SaveText.TextBox(_hdc, 310, 170, "00", 35, GRAY, LGRAY);
	SaveText.TextBox(_hdc, 310, 230, "00", 35, GRAY, LGRAY);
	SaveText.TextBox(_hdc, 310, 290, "00:00", 35, GRAY, LGRAY);

	if (m_SaveMenu_AnswerYes == 1)
	{
		if (m_SaveMenu_SaveCount == 1)
		{
			SaveText.TextBox(_hdc, 70, 490, "���ϸ� ����Ʈ�� �ۼ����Դϴ�.", 45, GRAY, LGRAY);

			SaveText.TextBox(_hdc, 70, 550, "������ ���� �ʵ��� ���ֽʽÿ�.", 45, GRAY, LGRAY);

		}
		else
		{
			IMG_MGR->GetImg("SaveBox2")->Render(_hdc, 650, 265, 250, 175);
			SaveText.TextBox(_hdc, 727, 297, "��", 45, GRAY, LGRAY);
			SaveText.TextBox(_hdc, 727, 357, "�ƴϿ�", 45, GRAY, LGRAY);

			if (m_SaveMenu_Num == 0)
			{
				SaveText.TextBox(_hdc, 677, 297, "��", 45, GRAY, LGRAY);
			}

			if (m_SaveMenu_Num == 1)
			{
				SaveText.TextBox(_hdc, 677, 357, "��", 45, GRAY, LGRAY);
			}

			SaveText.TextBox(_hdc, 70, 490, "���� �ۼ��� ����Ʈ��", 45, GRAY, LGRAY);

			SaveText.TextBox(_hdc, 70, 550, "����ᵵ �������ϱ�?", 45, GRAY, LGRAY);
		}
	}
	else if (m_SaveMenu_AnswerYes == 2)
	{
		SaveText.TextBox(_hdc, 70, 490, "���ϸ� ����Ʈ�� �ۼ����Դϴ�.", 45, GRAY, LGRAY);

		SaveText.TextBox(_hdc, 70, 550, "������ ���� �ʵ��� ���ֽʽÿ�.", 45, GRAY, LGRAY);

	}
	else
	{
		IMG_MGR->GetImg("SaveBox2")->Render(_hdc, 650, 265, 250, 175);
		SaveText.TextBox(_hdc, 727, 297, "��", 45, GRAY, LGRAY);
		SaveText.TextBox(_hdc, 727, 357, "�ƴϿ�", 45, GRAY, LGRAY);

		if (m_SaveMenu_Num == 0)
		{
			SaveText.TextBox(_hdc, 677, 297, "��", 45, GRAY, LGRAY);
		}

		if (m_SaveMenu_Num == 1)
		{
			SaveText.TextBox(_hdc, 677, 357, "��", 45, GRAY, LGRAY);
		}

		SaveText.TextBox(_hdc, 70, 490, "���ݱ����� Ȱ����", 45, GRAY, LGRAY);

		SaveText.TextBox(_hdc, 70, 550, "���ϸ� ����Ʈ�� �ۼ��ұ��?", 45, GRAY, LGRAY);
	}
}

void Scene_Report::Button_Down(int _key)
{
	if (VK_UP == _key)
	{
		m_SaveMenu_Num--;
		if (m_SaveMenu_Num < 0)
		{
			m_SaveMenu_Num = 1;
		}

	}
	if (VK_DOWN == _key)
	{
		m_SaveMenu_Num++;
		if (m_SaveMenu_Num > 1)
		{
			m_SaveMenu_Num = 0;
		}
	}
	if (VK_SPACE == _key)
	{
		if (m_SaveMenu_Num == 0)
		{
			m_SaveMenu_AnswerYes++;
			m_SaveMenu_SaveCount++;
			if (m_SaveMenu_AnswerYes > 2)
				m_SaveMenu_AnswerYes = 0;
				
		}

		if (m_SaveMenu_Num == 1)
		{
			m_SaveMenu_AnswerNo--;
			if (m_SaveMenu_AnswerNo < 0)
				m_SaveMenu_AnswerNo = 1;
		}
	}
}

bool Scene_Report::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
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