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
}

void Scene_Report::Update(float _elapseTime)
{
}

void Scene_Report::Render(HDC _hdc)
{
	//스크린샷
	BitBlt(_hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, SCENE_MGR.GetScreen(), 0, 0, SRCCOPY);

	IMG_MGR->GetImg("Dialog_01")->Render(_hdc, 20, 460, 920, 170);
	IMG_MGR->GetImg("SaveBox1")->Render(_hdc, 10, 20, 500, 340);

	SaveText.TextBox(_hdc, 30, 110, "주인공", 35, GRAY);
	SaveText.TextBox(_hdc, 30, 170, "가진 배지", 35, GRAY);
	SaveText.TextBox(_hdc, 30, 230, "포켓몬 도감", 35, GRAY);
	SaveText.TextBox(_hdc, 30, 290, "플레이 시간", 35, GRAY);

	// 바뀔 부분
	SaveText.TextBox(_hdc, 172, 52, "시티이름", 45, BLUE, LBLUE);
	SaveText.TextBox(_hdc, 260, 110, "닉네임", 40, GRAY, LGRAY);
	SaveText.TextBox(_hdc, 310, 170, "00", 35, GRAY, LGRAY);
	SaveText.TextBox(_hdc, 310, 230, "00", 35, GRAY, LGRAY);
	SaveText.TextBox(_hdc, 310, 290, "00:00", 35, GRAY, LGRAY);

	if (m_SaveMenu_AnswerYes == 1)
	{
		if (m_SaveMenu_SaveCount == 1)
		{
			SaveText.TextBox(_hdc, 70, 490, "포켓몬 리포트를 작성중입니다.", 45, GRAY, LGRAY);

			SaveText.TextBox(_hdc, 70, 550, "전원을 끄지 않도록 해주십시오.", 45, GRAY, LGRAY);

		}
		else
		{
			IMG_MGR->GetImg("SaveBox2")->Render(_hdc, 650, 265, 250, 175);
			SaveText.TextBox(_hdc, 727, 297, "예", 45, GRAY, LGRAY);
			SaveText.TextBox(_hdc, 727, 357, "아니오", 45, GRAY, LGRAY);

			if (m_SaveMenu_Num == 0)
			{
				SaveText.TextBox(_hdc, 677, 297, "▶", 45, GRAY, LGRAY);
			}

			if (m_SaveMenu_Num == 1)
			{
				SaveText.TextBox(_hdc, 677, 357, "▶", 45, GRAY, LGRAY);
			}

			SaveText.TextBox(_hdc, 70, 490, "전에 작성한 리포트에", 45, GRAY, LGRAY);

			SaveText.TextBox(_hdc, 70, 550, "덮어써도 괜찮습니까?", 45, GRAY, LGRAY);
		}
	}
	else if (m_SaveMenu_AnswerYes == 2)
	{
		SaveText.TextBox(_hdc, 70, 490, "포켓몬 리포트를 작성중입니다.", 45, GRAY, LGRAY);

		SaveText.TextBox(_hdc, 70, 550, "전원을 끄지 않도록 해주십시오.", 45, GRAY, LGRAY);

	}
	else
	{
		IMG_MGR->GetImg("SaveBox2")->Render(_hdc, 650, 265, 250, 175);
		SaveText.TextBox(_hdc, 727, 297, "예", 45, GRAY, LGRAY);
		SaveText.TextBox(_hdc, 727, 357, "아니오", 45, GRAY, LGRAY);

		if (m_SaveMenu_Num == 0)
		{
			SaveText.TextBox(_hdc, 677, 297, "▶", 45, GRAY, LGRAY);
		}

		if (m_SaveMenu_Num == 1)
		{
			SaveText.TextBox(_hdc, 677, 357, "▶", 45, GRAY, LGRAY);
		}

		SaveText.TextBox(_hdc, 70, 490, "지금까지의 활약을", 45, GRAY, LGRAY);

		SaveText.TextBox(_hdc, 70, 550, "포켓몬 리포트로 작성할까요?", 45, GRAY, LGRAY);
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
		case VK_UP:
		{
			m_SaveMenu_Num--;
			if (m_SaveMenu_Num < 0)
			{
				m_SaveMenu_Num = 1;
			}
		}break;
		case VK_DOWN:
		{
			m_SaveMenu_Num++;
			if (m_SaveMenu_Num > 1)
			{
				m_SaveMenu_Num = 0;
			}
		}break;
		case 'z':
		case 'Z':
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
		}break;
		case 'x':
		case 'X': {	SCENE_MGR.SetScene(SCENE_MENU); }break;

		case VK_ESCAPE: return true;	break;
		}
	}break;

	}
	return false;
}