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
	/*IMG_MGR->OpenImg("Images/UI/Dic_01.bmp");

	auto img = IMG_MGR->GetImg("Dic_01");

	if (img != nullptr)
	{
		img->SetTrans();
	}*/
}

void Scene_Dictionary::Update(float _elapseTime)
{
}

void Scene_Dictionary::Render(HDC _hdc)
{
	Text text;

	HDC _BGDC = IMG_MGR->GetImg("Dic_01")->GetImgDC();
	BitBlt(_hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, _BGDC, 0, 0, SRCCOPY);

	text.TextBox(_hdc, 210, 6, "���ϸ�    ����    ����", 50, WHITE);
	text.TextBox(_hdc, 15, 66, "���ϸ� ���", 50, ORANGE);
	text.TextBox(_hdc, 680, 113, "�߰���  ���ϸ�", 35, BLACK);
	text.TextBox(_hdc, 80, 120, "��ȣ ��", 50, BLACK);
	text.TextBox(_hdc, 15, 166, "����  ��ҿ�  ���  ���ϸ�", 50, ORANGE);
	text.TextBox(_hdc, 680, 203, "����  ���ϸ�", 35, BLACK);
	text.TextBox(_hdc, 80, 216, "�ʿ���  ���  ���ϸ�", 50, BLACK);
	text.TextBox(_hdc, 80, 266, "����  ���  ���ϸ�", 50, BLACK);
	text.TextBox(_hdc, 80, 316, "������  ���  ���ϸ�", 50, BLACK);
	text.TextBox(_hdc, 80, 366, "�ٴٿ�  ���  ���ϸ�", 50, BLACK);
	text.TextBox(_hdc, 80, 416, "������  ���  ���ϸ�", 50, BLACK);
	text.TextBox(_hdc, 80, 466, "�꿡  ���  ���ϸ�", 50, BLACK);
	text.TextBox(_hdc, 80, 516, "Ȳ�߿�  ���  ���ϸ�", 50, BLACK);
	text.TextBox(_hdc, 80, 566, "���ÿ�  ���  ���ϸ�", 50, BLACK);
	text.TextBox(_hdc, 80, 616, "�����  ���ϸ�", 50, BLACK);
	text.TextBox(_hdc, 15, 666, "���ϸ� ���", 50, ORANGE);
	text.TextBox(_hdc, 80, 716, "������  ��", 50, BLACK);
	text.TextBox(_hdc, 80, 766, "Ÿ��   ��", 50, BLACK);
	text.TextBox(_hdc, 80, 816, "����   ��", 50, BLACK);
	text.TextBox(_hdc, 80, 866, "ũ��   ��", 50, BLACK);
	text.TextBox(_hdc, 15, 916, "��Ÿ", 50, ORANGE);
	text.TextBox(_hdc, 80, 966, "������   �ݴ´�", 50, BLACK);
	text.TextBox(_hdc, 750, 595, "����", 35, WHITE);
	text.TextBox(_hdc, 865, 595, "����", 35, WHITE);
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
	text.TextBox(_hdc, 250, 6, "���ϸ�    ���", 50, WHITE);
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