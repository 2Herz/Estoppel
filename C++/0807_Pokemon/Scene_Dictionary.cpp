#include "stdafx.h"
#include "Scene_Dictionary.h"
#include "SceneMgr.h"

#pragma region
Scene_Dictionary::Scene_Dictionary(){}
Scene_Dictionary::~Scene_Dictionary(){}

void Scene_Dictionary::Init(HWND _hWnd){}
void Scene_Dictionary::Update(float _elapseTime){}
#pragma endregion 생성자, 소멸자, 초기화, 갱신

#pragma region
void Scene_Dictionary::Render(HDC _hdc)
{
	HDC _BGDC = IMG_MGR->GetImg("Dic_01")->GetImgDC();
	BitBlt(_hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, _BGDC, 0, 0, SRCCOPY);

	auto dic = IMG_MGR->GetImg("Dic_02");

	Create_Arrow(_hdc, m_ImgPos.x + 50, (m_CursorIndex * 113) + m_select, 2, true);
	text.TextBox(_hdc, m_ImgPos.x + 250, m_ImgPos.y + 11, Dictionary_Title, m_WordSize, WHITE);

	if (m_isFocus == false)
	{
		text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 66, m_category[0], m_WordSize, ORANGE);
		text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 66 + (m_WordSize * 2) + 20, m_category[2], m_WordSize, ORANGE);

		text.TextBox(_hdc, m_ImgPos.x + 750, m_ImgPos.y + 595, m_category[4], (m_WordSize - 5), WHITE);
		text.TextBox(_hdc, m_ImgPos.x + 865, m_ImgPos.y + 595, m_category[5], (m_WordSize - 5), WHITE);
		text.TextBox(_hdc, m_ImgPos.x + 680, m_ImgPos.y + 113, m_category[6], (m_WordSize - 10), BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 680, m_ImgPos.y + 203, m_category[7], (m_WordSize - 10), BLACK);

		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 116, m_category[1], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 66 + (m_WordSize * 3) + 40, m_category[3], m_WordSize, BLACK);
	}

	if (!m_isFocus)
	{
		switch (m_select)
		{
			case NUMBER:
			{
				if (isPopup)
				{
					Render_Dictionary_List(_hdc, WIN_WIDTH, WIN_HEIGHT);
				}
				dic->AniRender(_hdc, 0, 660, 340);

			}break;

			case CLOSE:
			{
				if (isPopup)
				{
					Render_Dictionary_Close();
				}
				dic->AniRender(_hdc, 1, 660, 340);

			}break;
		}
	}
}
#pragma endregion 도감 - 메인

#pragma region
void Scene_Dictionary::Render_Dictionary_List(HDC _hdc, int width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");

	Create_Arrow(_hdc, m_ImgPos.x + 50, m_ImgPos.y + 85 + m_select, 19, true);

	if (m_isFocus == false)
	{
		text.TextBox(_hdc, m_ImgPos.x + 310, m_ImgPos.y + 11, "포켓몬    목록", m_WordSize, WHITE);

		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 80, m_Numbering[0], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 80 + (m_WordSize), m_Numbering[1], m_WordSize, BLACK);
	}

	if (!m_isFocus)
	{
		for (int i = 2; i <= 11; i++)
		{
			text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 80 + (m_WordSize * i), m_Numbering[i], m_WordSize, BLACK);
		}
	}
}
#pragma endregion 도감 - 번호 순 

#pragma region
void Scene_Dictionary::Create_Arrow(HDC _hdc, int _posX, int _posY, int _MaxNum, bool _select)
{
	if (_select == false) return;

	auto select = IMG_MGR->GetImg("Select");
	select->Render(_hdc, _posX, _posY);
}
#pragma endregion 커서(화살표) 만드는 함수

#pragma region
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
					//	만약 NUMBER 라면....
					if (m_select == NUMBER)
					{
						m_CursorIndex--;
						m_select--;
					}
					//	NUMBER가 아니라면...
					else if(m_select != NUMBER)
					{
						m_CursorIndex--;
						m_select--;
						if (m_select <  (WIN_HEIGHT - 576))
							m_select = 0;
					}
				}break;
				case VK_DOWN:
				{
					if (m_select == NUMBER)
					{
						m_CursorIndex++;
						m_select++;
					}
					else if(m_select != NUMBER)
					{
						m_CursorIndex++;
						m_select++;
					}
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
#pragma endregion Windows Procedure