#include "stdafx.h"
#include "SceneMgr.h"

//	씬 클래스 포함
#include "Scene_Intro.h"
#include "Scene_Main.h"
#include "Scene_Menu.h"
#include "Scene_Dictionary.h"
#include "Scene_Pokemon.h"
#include "Scene_Bag.h"
#include "Scene_Trainer.h"
#include "Scene_Report.h"
#include "Scene_Setting.h"
///////////////////////////

SceneMgr::SceneMgr()
{
}
SceneMgr::~SceneMgr()
{
	delete m_pScene;
}

void SceneMgr::ChangeScene()
{
	delete m_pScene;

	switch (m_SceneType)
	{
	case SCENE_TYPE::SCENE_INTRO:	m_pScene = new Scene_Intro;			break;
	case SCENE_TYPE::SCENE_MAIN:	m_pScene = new Scene_Main;			break;
	case SCENE_TYPE::SCENE_MENU:	m_pScene = new Scene_Menu;			break;
	case SCENE_TYPE::SCENE_DIC:		m_pScene = new Scene_Dictionary;	break;
	case SCENE_TYPE::SCENE_POKEMON:	m_pScene = new Scene_Pokemon;		break;
	case SCENE_TYPE::SCENE_BAG:		m_pScene = new Scene_Bag;			break;
	case SCENE_TYPE::SCENE_TRAINER:	m_pScene = new Scene_Trainer;		break;
	case SCENE_TYPE::SCENE_REPORT:	m_pScene = new Scene_Report;		break;
	case SCENE_TYPE::SCENE_SETTING:	m_pScene = new Scene_Setting;		break;

	default: break;
	}

	m_isChange = false;
}

void SceneMgr::Init(HWND _hWnd)
{
	IMG_MGR->SethWnd(_hWnd);

	IMG_MGR->OpenImg("Images/UI/Dialog_00.bmp");
	IMG_MGR->OpenImg("Images/UI/Dialog_01.bmp");

	//	가방
	IMG_MGR->OpenImg("Images/UI/Bag_00_x4.bmp");
	IMG_MGR->OpenImg("Images/UI/Bag_01_x4.bmp");
	IMG_MGR->OpenImg("Images/UI/Arrow_Up_x4.bmp");
	IMG_MGR->OpenImg("Images/UI/Arrow_Down_x4.bmp");
	IMG_MGR->OpenImg("Images/UI/Arrow_Left_x4.bmp");
	IMG_MGR->OpenImg("Images/UI/Arrow_Right_x4.bmp");
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

	//	포켓몬
	IMG_MGR->OpenImg("Images/UI/Pokemon_00.bmp");
	IMG_MGR->OpenImg("Images/UI/Pokemon_01.bmp");
	IMG_MGR->OpenImg("Images/UI/Pokemon_02.bmp");
	IMG_MGR->OpenImg("Images/UI/Pokemon_03.bmp");
	auto	focusImg1 = IMG_MGR->GetImg("Pokemon_01");
	if (focusImg1 != nullptr)
	{
		focusImg1->SetTrans();
		focusImg1->SetFrame(2);
	}

	auto	focusImg2 = IMG_MGR->GetImg("Pokemon_02");
	if (focusImg2 != nullptr)
	{
		focusImg2->SetTrans();
		focusImg2->SetFrame(2);
	}

	auto	focusImg3 = IMG_MGR->GetImg("Pokemon_03");
	if (focusImg3 != nullptr)
	{
		focusImg3->SetTrans();
		focusImg3->SetFrame(2);
	}

	//	리포트
	IMG_MGR->OpenImg("Images/UI/SaveBox1.bmp");
	IMG_MGR->OpenImg("Images/UI/SaveBox2.bmp");
	IMG_MGR->OpenImg("Images/UI/SaveBox3.bmp");

	//	세팅
	IMG_MGR->OpenImg("Images/UI/SettingMenu.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuSBOX.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack0.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack1.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack2.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack3.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack4.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack5.bmp");
	IMG_MGR->OpenImg("Images/UI/SettingMenuBlack6.bmp");

	//	사전
	IMG_MGR->OpenImg("Images/UI/Dic_01.bmp");

	m_box.Init(_hWnd);
}

void SceneMgr::Update(float _elapseTime)
{
	if (m_isChange == true) ChangeScene();

	if (m_pScene == nullptr) return;

	m_pScene->Update(_elapseTime);
}

void SceneMgr::Render(HDC _hdc)
{
	if (_hdc == nullptr || m_pScene == nullptr) return;

	m_pScene->Render(_hdc);
}

bool SceneMgr::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	if (m_pScene == nullptr) return false;

	return m_pScene->WndProc(_hWnd, _message, _wParam, _lParam);
}
