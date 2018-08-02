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

	text.TextBox(_hdc, m_ImgPos.x + 250, m_ImgPos.y + 11, Dictionary_Title, m_WordSize, WHITE);

	for (int i = 0; i < m_ViewCount + 1; i++)
	{
		textList.push_back(i);
	}

	if (!m_isDraw)
	{
		for (int i = 0; i < m_ViewCount; i++)
		{
			if (i + m_TopIndex >= textList.size()) break;

			if (m_CursorIndex == i + m_TopIndex)
			{
				text.TextBox(_hdc, m_ImgPos.x + 40, m_ImgPos.y + 110, "▶", 35, BLACK, BLACK);
			}
		}
		m_isDraw = false;
	}

	if (m_isFocus == false)
	{
		text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 66, m_category[0], m_WordSize, ORANGE);
		text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 156, m_category[1], m_WordSize, ORANGE);
		text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 206 + (m_WordSize * 9), m_category[12], m_WordSize, ORANGE);
		text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 206 + (m_WordSize * 14) + 30, m_category[17], m_WordSize, ORANGE);
	}

	if (!m_isFocus)
	{
		//	번호 순
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 110, m_category[2], m_WordSize, BLACK);
		//	초원 ~ 희귀한
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 204, m_category[3], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 204 + (m_WordSize), m_category[4], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 204 + (m_WordSize * 2), m_category[5], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 204 + (m_WordSize * 3), m_category[6], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 204 + (m_WordSize * 4), m_category[7], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 204 + (m_WordSize * 5), m_category[8], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 204 + (m_WordSize * 6), m_category[9], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 204 + (m_WordSize * 7), m_category[10], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 204 + (m_WordSize * 8), m_category[11], m_WordSize, BLACK);
		//	정렬
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 10), m_category[13], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 11), m_category[14], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 12), m_category[15], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 13), m_category[16], m_WordSize, BLACK);
		//	기타
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 206 + (m_WordSize * 15) + 30, m_category[18], m_WordSize, BLACK);
	}

	text.TextBox(_hdc, m_ImgPos.x + 750, m_ImgPos.y + 595, m_category[19], (m_WordSize - 5), WHITE);
	text.TextBox(_hdc, m_ImgPos.x + 865, m_ImgPos.y + 595, m_category[20], (m_WordSize - 5), WHITE);
	text.TextBox(_hdc, m_ImgPos.x + 680, m_ImgPos.y + 113, m_category[21], (m_WordSize - 10), BLACK);
	text.TextBox(_hdc, m_ImgPos.x + 680, m_ImgPos.y + 203, m_category[22], (m_WordSize - 10), BLACK);

	if (m_isKey)
	{
		char key = GetAsyncKeyState(key) & 0x8000;

		switch (key)
		{
		case VK_UP:
			if (m_CursorIndex < textList.size() - 1) m_CursorIndex++;
			break;
		case VK_DOWN:
			if (m_CursorIndex > 0) m_CursorIndex--;
			break;
		}

		if (m_CursorIndex < m_TopIndex) m_TopIndex = m_CursorIndex;
		if (m_CursorIndex >= m_TopIndex + m_ViewCount) m_TopIndex = m_CursorIndex - m_ViewCount + 1;

		m_isDraw = true;
	}
}

bool Scene_Dictionary::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
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

void Scene_Dictionary::Render_Dictionary_List(HDC _hdc, int width, int _height)
{
	Text text;
	auto img = IMG_MGR->GetImg("Dic_01");
	text.TextBox(_hdc, 250, 6, "포켓몬    목록", 50, WHITE);
	text.TextBox(_hdc, 100, 60, "No001  - - - - -", 50, BLACK);
	text.TextBox(_hdc, 100, 110, "No002  - - - - -", 50, BLACK);
	text.TextBox(_hdc, 100, 160, "No003  - - - - -", 50, BLACK);
	text.TextBox(_hdc, 100, 210, "No004  - - - - -", 50, BLACK);
	text.TextBox(_hdc, 100, 260, "No005  - - - - -", 50, BLACK);
}

void Scene_Dictionary::Render_Dictionary_GrassLand(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Forest(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_WaterFront(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Sea(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Cave(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Mountain(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Wilderness(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_City(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Rare(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Sort(int _select)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Sort_Order()
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Sort_Type(int _select, int _type)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Sort_Weight(int _select, int _weight)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Sort_Size(int _select, int _size)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void Scene_Dictionary::Render_Dictionary_Etc_Close()
{
	auto img = IMG_MGR->GetImg("Dic_01");
}