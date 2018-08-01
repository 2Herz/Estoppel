#include "DictionaryUI.h"

typedef TextUI Text;
typedef BoxUI Box;

DictionaryUI::DictionaryUI()
{
}

DictionaryUI::~DictionaryUI()
{
	IMG_MGR->Destroy();
}

void DictionaryUI::Init(HWND _hWnd)
{
	IMG_MGR->SethWnd(_hWnd);
	IMG_MGR->OpenImg("Image/Dic_01.bmp", m_imgWidth, m_imgHeight);

	auto img = IMG_MGR->GetImg("Dic_01");

	if (img != nullptr)
	{
		img->SetTrans();
	}
}

void DictionaryUI::Render_Main_Dictionary(HDC _hdc, int _width, int _height)
{
	Text text;

	HDC _BGDC = IMG_MGR->GetImg("Dic_01")->GetImgDC();
	BitBlt(_hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, _BGDC, 0, 0, SRCCOPY);

	text.TextBox(_hdc, (m_ImgPos.x + 210),(m_ImgPos.y + 11), "포켓몬    도감    목차", m_WordSize, WHITE);
	if (m_ImgPos.y < (WIN_HEIGHT - 576) && m_ImgPos.y < (WIN_HEIGHT - 128))
	{
		text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 66, m_str[0], m_WordSize, ORANGE);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 120, m_str[1], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 166, m_str[2], m_WordSize, ORANGE);

		for (int i = 3; i <= 11; i++)
		{
			text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY, m_str[3], m_WordSize, BLACK);
			text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY + m_WordSize, m_str[4], m_WordSize, BLACK);
			text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY + (m_WordSize * 2), m_str[5], m_WordSize, BLACK);
		}

		text.TextBox(_hdc, (m_ImgPos.x + 15), (m_ImgPos.y + 256), m_str[12], m_WordSize, ORANGE);

		for (int i = 11; i <= 14; i++)
		{
			text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 296, m_str[13], m_WordSize, BLACK);
			text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 296 + 41, m_str[14], m_WordSize, BLACK);
			text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 296 + 81, m_str[15], m_WordSize, BLACK);
			text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 296 + 121, m_str[16], m_WordSize, BLACK);
		}

		text.TextBox(_hdc, m_ImgPos.x + 15, m_ImgPos.y + 296 + (m_WordSize * 4) + 30, m_str[17], m_WordSize, ORANGE);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 296 + (m_WordSize * 5) + 30, m_str[18], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 750, m_ImgPos.y + 595, "선택", (m_WordSize - 5), WHITE);
		text.TextBox(_hdc, m_ImgPos.x + 865, m_ImgPos.y + 595, "결정", (m_WordSize - 5), WHITE);
		text.TextBox(_hdc, m_ImgPos.x + 680, m_ImgPos.y + 113, "발견한  포켓몬", (m_WordSize - 5), BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 680, m_ImgPos.y + 203, "잡은  포켓몬", (m_WordSize - 5), BLACK);

		//	화살표 : 기본값 false
		if (m_isSelect == false)	return;

		auto select = IMG_MGR->GetImg("Select");
		select->AniRender(_hdc, 0, (m_ImgPos.x + 80) * m_CellSize.cx, (m_ImgPos.y + 120) + (m_Select * 2) * m_CellSize.cy);

		if (m_isClick == false)
		{
			if (KEYMGR.OnceKeyDown(VK_DOWN))
			{
				m_Select++;
				if (m_Select > m_MaxNum - 1)
					m_Select = 0;
			}
			if (KEYMGR.OnceKeyDown(VK_UP))
			{
				m_Select--;
				if (m_Select < 0)
					m_Select = m_MaxNum - 1;
			}
		}
	}
}

void DictionaryUI::Render_Dictionary_List(HDC _hdc, int width, int _height)
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

void DictionaryUI::Render_Dictionary_GrassLand(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Forest(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_WaterFront(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Sea(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Cave(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Mountain(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Wilderness(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_City(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Rare(HDC _hdc, int _width, int _height)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Sort_Order()
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Sort_Type(int _select, int _type)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Sort_Weight(int _select, int _weight)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}

void DictionaryUI::Render_Dictionary_Sort_Size(int _select, int _size)
{
	auto img = IMG_MGR->GetImg("Dic_01");
}