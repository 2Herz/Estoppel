#include "stdafx.h"
#include "Scene_Dictionary.h"
#include "SceneMgr.h"

typedef TextUI Text;

Scene_Dictionary::Scene_Dictionary()
{
}

Scene_Dictionary::~Scene_Dictionary()
{
}

void Scene_Dictionary::Init(HWND _hWnd)
{
}

void Scene_Dictionary::Update(float _elapseTime)
{
}

void Scene_Dictionary::Render(HDC _hdc)
{
	Text text;

	HDC _BGDC = IMG_MGR->GetImg("Dic_01")->GetImgDC();
	BitBlt(_hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, _BGDC, 0, 0, SRCCOPY);

	auto dic = IMG_MGR->GetImg("Dic_02");

	Create_Arrow(_hdc, m_ImgPos.x + 50, m_ImgPos.y + 116 + m_select, 2, true);

	text.TextBox(_hdc, m_ImgPos.x + 250, m_ImgPos.y + 11, Dictionary_Title, m_WordSize, WHITE);

	if (m_isFocus == false)
	{
		text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 66, m_category[0], m_WordSize, ORANGE);
		text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 66 + (m_WordSize * 2) + 20, m_category[2], m_WordSize, ORANGE);

		text.TextBox(_hdc, m_ImgPos.x + 750, m_ImgPos.y + 595, m_category[4], (m_WordSize - 5), WHITE);
		text.TextBox(_hdc, m_ImgPos.x + 865, m_ImgPos.y + 595, m_category[5], (m_WordSize - 5), WHITE);
		text.TextBox(_hdc, m_ImgPos.x + 680, m_ImgPos.y + 113, m_category[6], (m_WordSize - 10), BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 680, m_ImgPos.y + 203, m_category[7], (m_WordSize - 10), BLACK);
	}

	if (!m_isFocus)
	{
		switch (m_select)
		{
			case NUMBER:
			{
				text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 116, m_category[1], m_WordSize, BLACK);
				dic->AniRender(_hdc, 0, 660, 340);
				if (isPopup)
				{
					Render_Dictionary_List(_hdc, WIN_WIDTH, WIN_HEIGHT);
				}
			}break;

			case CLOSE:
			{
				text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 66 + (m_WordSize * 3) + 20, m_category[3], m_WordSize, BLACK);
				dic->AniRender(_hdc, 1, 660, 340);
				if (isPopup)
				{
					Render_Dictionary_Close();
				}
			}break;
		}
	}
}

void Scene_Dictionary::Render_Dictionary_List(HDC _hdc, int width, int _height)
{
	Text text;
	auto img = IMG_MGR->GetImg("Dic_01");

	Create_Arrow(_hdc, m_ImgPos.x + 50, m_ImgPos.y + 85 + m_select, 19, true);

	text.TextBox(_hdc, m_ImgPos.x + 310, m_ImgPos.y + 11, "포켓몬    목록", m_WordSize, WHITE);

	text.TextBox(_hdc, 100, 80,										m_Numbering[0],		m_WordSize, BLACK);
	text.TextBox(_hdc, 100, 80 +				(m_WordSize),		m_Numbering[1],		m_WordSize, BLACK);
	text.TextBox(_hdc, 100, 80 +				(m_WordSize * 2),	m_Numbering[2],		m_WordSize, BLACK);
	text.TextBox(_hdc, 100, 80 +				(m_WordSize * 3),	m_Numbering[3],		m_WordSize, BLACK);
	text.TextBox(_hdc, 100, 80 +				(m_WordSize * 4),	m_Numbering[4],		m_WordSize, BLACK);
	text.TextBox(_hdc, 100, 80 +				(m_WordSize * 5),	m_Numbering[5],		m_WordSize, BLACK);
	text.TextBox(_hdc, 100, 80 +				(m_WordSize * 6),	m_Numbering[6],		m_WordSize, BLACK);
	text.TextBox(_hdc, 100, 80 +				(m_WordSize * 7),	m_Numbering[7],		m_WordSize, BLACK);
	text.TextBox(_hdc, 100, 80 +				(m_WordSize * 8),	m_Numbering[8],		m_WordSize, BLACK);
	text.TextBox(_hdc, 100, 80 +				(m_WordSize * 9),	m_Numbering[9],		m_WordSize, BLACK);
	text.TextBox(_hdc, 100, 80 +				(m_WordSize * 10),	m_Numbering[10],		m_WordSize, BLACK);
	text.TextBox(_hdc, 100, 80 +				(m_WordSize * 11),	m_Numbering[11],		m_WordSize, BLACK);
}

void Scene_Dictionary::Create_Arrow(HDC _hdc, int _posX, int _posY, int _MaxNum, bool _select)
{
	if (_select == false) return;

	auto select = IMG_MGR->GetImg("Select");
	select->Render(_hdc, _posX, _posY);
}

bool Scene_Dictionary::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case VK_UP:
		{
			if (m_select == NUMBER)
			{
				m_select--;
				if (m_select < (WIN_HEIGHT - 576))
					m_select = 0;;
			}
			else
			{
				m_select--;
				if (m_select < (WIN_HEIGHT - 576))
					m_select = 0;;
			}
		}break;
		case VK_DOWN:
		{
			if (m_select == NUMBER)
			{
				m_select++;
			}
			else
				m_select++;
		}break;

		case 's':
		case 'S':
		{
			if (isPopup)
			{
				isPopup = false;
			}
			else
			{
				isPopup = true;
			}
		}break;

		case 'z':
		case 'Z':
		{
			Render_Dictionary_Close();
		}break;
		case 'x':
		case 'X': {	SCENE_MGR.SetScene(SCENE_MENU); }break;

		case VK_ESCAPE: return true;	break;
		}
	}break;

	}
	return false;
}