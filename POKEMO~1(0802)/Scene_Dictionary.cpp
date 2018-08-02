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

	text.TextBox(_hdc, 210, 6, "포켓몬    도감    목차", 50, WHITE);
	text.TextBox(_hdc, 15, 66, "포켓몬 목록", 50, ORANGE);
	text.TextBox(_hdc, 680, 113, "발견한  포켓몬", 35, BLACK);
	text.TextBox(_hdc, 80, 120, "번호 순", 50, BLACK);
	text.TextBox(_hdc, 15, 166, "여러  장소에  사는  포켓몬", 50, ORANGE);
	text.TextBox(_hdc, 680, 203, "잡은  포켓몬", 35, BLACK);
	text.TextBox(_hdc, 80, 216, "초원에  사는  포켓몬", 50, BLACK);
	text.TextBox(_hdc, 80, 266, "숲에  사는  포켓몬", 50, BLACK);
	text.TextBox(_hdc, 80, 316, "물가에  사는  포켓몬", 50, BLACK);
	text.TextBox(_hdc, 80, 366, "바다에  사는  포켓몬", 50, BLACK);
	text.TextBox(_hdc, 80, 416, "동굴에  사는  포켓몬", 50, BLACK);
	text.TextBox(_hdc, 80, 466, "산에  사는  포켓몬", 50, BLACK);
	text.TextBox(_hdc, 80, 516, "황야에  사는  포켓몬", 50, BLACK);
	text.TextBox(_hdc, 80, 566, "도시에  사는  포켓몬", 50, BLACK);
	text.TextBox(_hdc, 80, 616, "희귀한  포켓몬", 50, BLACK);
	text.TextBox(_hdc, 15, 666, "포켓몬 목록", 50, ORANGE);
	text.TextBox(_hdc, 80, 716, "가나다  순", 50, BLACK);
	text.TextBox(_hdc, 80, 766, "타입   순", 50, BLACK);
	text.TextBox(_hdc, 80, 816, "무게   순", 50, BLACK);
	text.TextBox(_hdc, 80, 866, "크기   순", 50, BLACK);
	text.TextBox(_hdc, 15, 916, "기타", 50, ORANGE);
	text.TextBox(_hdc, 80, 966, "도감을   닫는다", 50, BLACK);
	text.TextBox(_hdc, 750, 595, "선택", 35, WHITE);
	text.TextBox(_hdc, 865, 595, "결정", 35, WHITE);
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