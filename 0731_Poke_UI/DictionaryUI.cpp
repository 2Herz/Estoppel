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

	text.TextBox(_hdc, (m_ImgPos.x + 210),(m_ImgPos.y + 6), "���ϸ�    ����    ����", 40, WHITE);
	text.TextBox(_hdc, (m_ImgPos.x + 15),(m_ImgPos.y + 66), "���ϸ� ���", 40, ORANGE);
	text.TextBox(_hdc, (m_ImgPos.x + 680),(m_ImgPos.y + 113), "�߰���  ���ϸ�", 35, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 120), "��ȣ ��", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 15),(m_ImgPos.y + 166), "����  ��ҿ�  ���  ���ϸ�", 40, ORANGE);
	text.TextBox(_hdc, (m_ImgPos.x + 680),(m_ImgPos.y + 203), "����  ���ϸ�", 35, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 216), "�ʿ���  ���  ���ϸ�", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 266), "����  ���  ���ϸ�", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 316), "������  ���  ���ϸ�", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 366), "�ٴٿ�  ���  ���ϸ�", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 416), "������  ���  ���ϸ�", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 466), "�꿡  ���  ���ϸ�", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 516), "Ȳ�߿�  ���  ���ϸ�", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 566), "���ÿ�  ���  ���ϸ�", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 616), "�����  ���ϸ�", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 15),(m_ImgPos.y + 666), "���ϸ� ���", 40, ORANGE);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 716), "������  ��", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 766), "Ÿ��   ��", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 816), "����   ��", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 866), "ũ��   ��", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 15),(m_ImgPos.y + 916), "��Ÿ", 40, ORANGE);
	text.TextBox(_hdc, (m_ImgPos.x + 80),(m_ImgPos.y + 966), "������   �ݴ´�", 40, BLACK);
	text.TextBox(_hdc, (m_ImgPos.x + 750),(m_ImgPos.y + 595), "����", 35, WHITE);
	text.TextBox(_hdc, (m_ImgPos.x + 865),(m_ImgPos.y + 595), "����", 35, WHITE);

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
	text.TextBox(_hdc, 250, 6, "���ϸ�    ���", 50, WHITE);
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