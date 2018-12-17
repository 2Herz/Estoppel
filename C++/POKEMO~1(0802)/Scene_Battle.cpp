#include "stdafx.h"
#include "Scene_Battle.h"
#include "SceneMgr.h"


Scene_Battle::Scene_Battle()
{
}


Scene_Battle::~Scene_Battle()
{
}

void Scene_Battle::Init(HWND _hWnd)
{
	IMG_MGR->OpenImg("Images/UI/Battle_bg_x4.bmp");	//	배경
	IMG_MGR->OpenImg("Images/UI/Battle_grass_x4.bmp");	//	배경
	IMG_MGR->OpenImg("Images/UI/Dialog_02.bmp");		//	대화창
	
	m_BGDC = IMG_MGR->GetImg("Battle_bg_x4")->GetImgDC();
	m_BGDC1 = IMG_MGR->GetImg("Dialog_02")->GetImgDC();

	auto	field = IMG_MGR->GetImg("Battle_grass_x4");
	if (field != nullptr)
	{
		field->SetTrans();
		field->SetFrame(1);
	}
}

void Scene_Battle::Update(float _elapseTime)
{
}

void Scene_Battle::Render(HDC _hdc)
{
	BitBlt(_hdc, 0, 0, WIN_WIDTH, 448, m_BGDC, 0, 0, SRCCOPY);
	BitBlt(_hdc, 0, 448, WIN_WIDTH, 192, m_BGDC1, 0, 0, SRCCOPY);
	auto	field1	= IMG_MGR->GetImg("Battle_grass_x4");
	auto	field2	= IMG_MGR->GetImg("Battle_grass_x4");

	field1->AniRender(_hdc, 0, 750, 140);
}

bool Scene_Battle::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
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