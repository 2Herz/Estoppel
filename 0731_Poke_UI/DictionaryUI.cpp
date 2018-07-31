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

	text.TextBox(_hdc, (m_ImgPos.x + 210),(m_ImgPos.y + 6), "포켓몬    도감    목차", m_WordSize, WHITE);
	text.TextBox(_hdc, (m_ImgPos.x + 15),(m_ImgPos.y + 66), "포켓몬 목록", m_WordSize, ORANGE);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 120), m_str[0], m_WordSize, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 15),(m_ImgPos.y + 166), "여러  장소에  사는  포켓몬", m_WordSize, ORANGE);
	for (int i = 1; i <= 9; i++)
	{
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY, m_str[i], m_WordSize, BLACK);
		i++;
		/*text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY, m_str[1], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY + 40, m_str[2], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY + 80, m_str[3], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY + 120, m_str[4], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY + 160, m_str[5], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY + 200, m_str[6], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY + 240, m_str[7], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY + 280, m_str[8], m_WordSize, BLACK);
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + m_posY + 320, m_str[9], m_WordSize, BLACK);*/
	}

	//text.TextBox(_hdc, (m_ImgPos.x + 15), (m_ImgPos.y + 286), "정  렬", m_WordSize, ORANGE);
	/*for (int i = 11; i <= 14; i++)
	{
		text.TextBox(_hdc, m_ImgPos.x + 80, m_ImgPos.y + 326, m_str[i], m_WordSize, BLACK);
	}
	text.TextBox(_hdc, (m_ImgPos.x + 15),(m_ImgPos.y + 916), "기타", m_WordSize, ORANGE);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 966), "도감을   닫는다", m_WordSize, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 750),(m_ImgPos.y + 595), "선택", (m_WordSize - 5), WHITE);
	text.TextBox(_hdc, (m_ImgPos.x + 865),(m_ImgPos.y + 595), "결정", (m_WordSize - 5), WHITE);*/
	text.TextBox(_hdc, (m_ImgPos.x + 680), (m_ImgPos.y + 113), "발견한  포켓몬", (m_WordSize - 5), BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 680), (m_ImgPos.y + 203), "잡은  포켓몬", m_WordSize, BLACK);

	/*if (m_isClick == false)
	{
		if (KEYMGR.OnceKeyDown(VK_UP))
		{
			m_scrollY += 40;
			m_Select++;
			if (m_Select < 0)
				m_Select = WIN_HEIGHT - 576;
		}
		if (KEYMGR.OnceKeyDown(VK_DOWN))
		{
			m_scrollY -= 40;
			m_Select++;
			if (m_Select > WIN_HEIGHT - 128)
				m_Select = 0;
		}
	}
	
	switch (m_Select)
	{
		case DS_LIST:
		{
			Render_Dictionary_List(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case DS_GRASSLAND:
		{
			Render_Dictionary_GrassLand(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case DS_FOREST:
		{
			Render_Dictionary_Forest(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case DS_WATERFRONT:
		{
			Render_Dictionary_WaterFront(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case DS_SEA:
		{
			Render_Dictionary_Sea(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case DS_CAVE:
		{
			Render_Dictionary_Cave(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case DS_MOUNTAIN:
		{
			Render_Dictionary_Mountain(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case DS_WILDERNESS:
		{
			Render_Dictionary_Wilderness(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case DS_CITY:
		{
			Render_Dictionary_City(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case DS_RARE:
		{
			Render_Dictionary_Rare(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case DS_SORT_ORDER:
		{

		}break;
		case DS_SORT_TYPE:
		{

		}break;
		case DS_SORT_WEIGHT:
		{

		}break;
		case DS_SORT_SIZE:
		{

		}break;
		case DS_ETC:
		break;
	}

	if (KEYMGR.OnceKeyDown('Z'))
	{
		m_isClick = !m_isClick;
	}

	if (m_isClick == true)
	{
		switch (m_Select)
		{
		case 0:
		{
			Render_Dictionary_List(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;

		case 1:
		{
			Render_Dictionary_GrassLand(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;

		case 2:
		{
			Render_Dictionary_Forest(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;

		case 3:
		{
			Render_Dictionary_WaterFront(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;

		case 4:
		{
			Render_Dictionary_Sea(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;

		case 5:
		{
			Render_Dictionary_Cave(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case 6:
		{
			Render_Dictionary_Mountain(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case 7:
		{
			Render_Dictionary_Wilderness(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case 8:
		{
			Render_Dictionary_City(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case 9:
		{
			Render_Dictionary_Rare(_hdc, WIN_WIDTH, WIN_HEIGHT);
		}break;
		case 10:
		{

		}break;
		case 11:
		{

		}break;
		case 12:
		{

		}break;
		case 13:
		{

		}break;
		case 14:
		{

		}break;
		case 15:
		{

		}break;
		}
	}*/
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