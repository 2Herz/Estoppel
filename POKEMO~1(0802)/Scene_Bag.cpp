#include "stdafx.h"
#include "Scene_Bag.h"
#include "SceneMgr.h"


Scene_Bag::Scene_Bag()
{
	m_BGDC = IMG_MGR->GetImg("Bag_00_x4")->GetImgDC();
}


Scene_Bag::~Scene_Bag()
{
}

void Scene_Bag::Init(HWND _hWnd)
{
	/*IMG_MGR->OpenImg("Images/UI/Bag_00_x4.bmp");	//	배경
	IMG_MGR->OpenImg("Images/UI/Bag_01_x4.bmp");	//	가방이미지
	IMG_MGR->OpenImg("Images/UI/Arrow_Up_x4.bmp");		//	방향키
	IMG_MGR->OpenImg("Images/UI/Arrow_Down_x4.bmp");	//	
	IMG_MGR->OpenImg("Images/UI/Arrow_Left_x4.bmp");	//	
	IMG_MGR->OpenImg("Images/UI/Arrow_Right_x4.bmp");	//	
	//IMG_MGR->OpenImg("Images/UI/Bag_03.bmp");

	m_BGDC = IMG_MGR->GetImg("Bag_00_x4")->GetImgDC();

	auto	bagImg = IMG_MGR->GetImg("Bag_01_x4");
	if (bagImg != nullptr)
	{
		bagImg->SetTrans();
		bagImg->SetFrame(4);
	}

	auto	arrowUp = IMG_MGR->GetImg("Arrow_Up_x4");
	if (arrowUp != nullptr)
	{
		arrowUp->SetTrans();
		arrowUp->SetFrame(6);
		
	}
	auto	arrowDown = IMG_MGR->GetImg("Arrow_Down_x4");
	if (arrowDown != nullptr)
	{
		arrowDown->SetTrans();
		arrowDown->SetFrame(6);
	}
	auto	arrowLeft = IMG_MGR->GetImg("Arrow_Left_x4");
	if (arrowLeft != nullptr)
	{
		arrowLeft->SetTrans();
		arrowLeft->SetFrame(6);
	}
	auto	arrowRight = IMG_MGR->GetImg("Arrow_Right_x4");
	if (arrowRight != nullptr)
	{
		arrowRight->SetTrans();
		arrowRight->SetFrame(6);
	}	
	*/
}

void Scene_Bag::Update(float _elapseTime)
{
	m_time += _elapseTime;

	if (0.1f <= m_time)
	{
		m_time -= 0.2f;
		m_Ani++;

		if (m_Ani > 5)
		{
			m_Ani = 0;
		}
	}
}

void Scene_Bag::Render(HDC _hdc)
{
	BitBlt(_hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, m_BGDC, 0, 0, SRCCOPY);
	auto	bagImg		= IMG_MGR->GetImg("Bag_01_x4");
	auto	arrowUp		= IMG_MGR->GetImg("Arrow_Up_x4");
	auto	arrowDown	= IMG_MGR->GetImg("Arrow_Down_x4");
	auto	arrowLeft	= IMG_MGR->GetImg("Arrow_Left_x4");
	auto	arrowRight	= IMG_MGR->GetImg("Arrow_Right_x4");
	
	if (KEY_MANAGER.OnceKeyDown(VK_LEFT))
	{
		m_BagNum--;
		if (m_BagNum < 0)
			m_BagNum = 0;
	}
	else if (KEY_MANAGER.OnceKeyDown(VK_RIGHT))
	{
		m_BagNum++;
		if (m_BagNum > 2)
			m_BagNum = 2;
	}
	/*if (KEYMGR.OnceKeyDown(VK_SPACE))
	{
		m_Ani.Start();
	}*/

	
	switch (m_BagNum)
	{
	case 0:		//	도구
	{
		bagImg->AniRender(_hdc, 0, 46, 140);
		m_Txt.TextBox(_hdc, 120, 40, "도구", 35, WHITE, GRAY);
	}break;

	case 1:		//	중요한 물건
	{
		bagImg->AniRender(_hdc, 1, 46, 140);
		m_Txt.TextBox(_hdc, 80, 40, "중요한 물건", 35, WHITE, GRAY);
	}break;

	case 2:		//	볼
	{
		bagImg->AniRender(_hdc, 2, 46, 140);
		m_Txt.TextBox(_hdc, 140, 40, "볼", 35, WHITE, GRAY);
	}break;
	}

	
	//arrowRight->AniRender(_hdc, m_Ani.m_nowIndex, 270, 260);
	arrowLeft->AniRender(_hdc, m_Ani, 0, 260);
	arrowRight->AniRender(_hdc, m_Ani, 270, 260);
	arrowUp->AniRender(_hdc, m_Ani, 610, 0);
	arrowDown->AniRender(_hdc, m_Ani, 610, 400);
	//m_Ani.Start();
}

bool Scene_Bag::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
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