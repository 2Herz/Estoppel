#include "stdafx.h"
#include "SceneMgr.h"

//	씬 클래스 포함
#include "Scene_Intro.h"
#include "Scene_Main.h"
#include "Scene_Menu.h"
#include "Scene_Dictionary.h"
#include "Scene_Pokemon.h"
#include "Scene_Info.h"
#include "Scene_Bag.h"
#include "Scene_Trainer.h"
#include "Scene_Report.h"
#include "Scene_Setting.h"
#include "Scene_Battle.h"
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
	case SCENE_TYPE::SCENE_INFO:	m_pScene = new Scene_Info;			break;
	case SCENE_TYPE::SCENE_BAG:		m_pScene = new Scene_Bag;			break;
	case SCENE_TYPE::SCENE_TRAINER:	m_pScene = new Scene_Trainer;		break;
	case SCENE_TYPE::SCENE_REPORT:	m_pScene = new Scene_Report;		break;
	case SCENE_TYPE::SCENE_SETTING:	m_pScene = new Scene_Setting;		break;
	case SCENE_TYPE::SCENE_BATTLE:	m_pScene = new Scene_Battle;		break;

	default: break;
	}
	m_isChange = false;
}

void SceneMgr::Init(HWND _hWnd)
{
	m_tempScreen.CreateImg(_hWnd, WIN_WIDTH, WIN_HEIGHT);
	IMG_MGR->SethWnd(_hWnd);

	IMG_MGR->OpenImg("Images/UI/Dialog_00.bmp");
	IMG_MGR->OpenImg("Images/UI/Dialog_01.bmp");

	//	가방
	IMG_MGR->OpenImg("Images/UI/Bag_00.bmp");
	IMG_MGR->OpenImg("Images/UI/Bag_01.bmp");
	IMG_MGR->OpenImg("Images/UI/Arrow_Up.bmp");
	IMG_MGR->OpenImg("Images/UI/Arrow_Down.bmp");
	IMG_MGR->OpenImg("Images/UI/Arrow_Left.bmp");
	IMG_MGR->OpenImg("Images/UI/Arrow_Right.bmp");
	IMG_MGR->OpenImg("Images/UI/Item.bmp");

	auto	bagImg = IMG_MGR->GetImg("Bag_01");
	if (bagImg != nullptr)
	{
		bagImg->SetTrans();
		bagImg->SetFrame(4);
	}

	auto	arrowUp = IMG_MGR->GetImg("Arrow_Up");
	if (arrowUp != nullptr)
	{
		arrowUp->SetTrans();
		arrowUp->SetFrame(6);

	}
	auto	arrowDown = IMG_MGR->GetImg("Arrow_Down");
	if (arrowDown != nullptr)
	{
		arrowDown->SetTrans();
		arrowDown->SetFrame(6);
	}
	auto	arrowLeft = IMG_MGR->GetImg("Arrow_Left");
	if (arrowLeft != nullptr)
	{
		arrowLeft->SetTrans();
		arrowLeft->SetFrame(6);
	}
	auto	arrowRight = IMG_MGR->GetImg("Arrow_Right");
	if (arrowRight != nullptr)
	{
		arrowRight->SetTrans();
		arrowRight->SetFrame(6);
	}
	auto	itemImg = IMG_MGR->GetImg("Item");
	if (itemImg != nullptr)
	{
		itemImg->SetTrans();
		itemImg->SetFrame(28);
	}

	//	포켓몬
	IMG_MGR->OpenImg("Images/UI/Pokemon_00.bmp");
	IMG_MGR->OpenImg("Images/UI/Pokemon_01.bmp");
	IMG_MGR->OpenImg("Images/UI/Pokemon_02.bmp");
	IMG_MGR->OpenImg("Images/UI/Pokemon_03.bmp");
	IMG_MGR->OpenImg("Images/UI/PokemonChange_01.bmp");
	IMG_MGR->OpenImg("Images/UI/PokemonChange_02.bmp");
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

	auto	changeImg1 = IMG_MGR->GetImg("PokemonChange_01");
	if (changeImg1 != nullptr)
	{
		changeImg1->SetTrans();
		changeImg1->SetFrame(2);
	}

	auto	changeImg2 = IMG_MGR->GetImg("PokemonChange_02");
	if (changeImg2 != nullptr)
	{
		changeImg2->SetTrans();
		changeImg2->SetFrame(2);
	}
	
	//	Info(포켓몬 상태보기)
	IMG_MGR->OpenImg("Images/UI/Info_01.bmp");
	IMG_MGR->OpenImg("Images/UI/Info_02.bmp");
	IMG_MGR->OpenImg("Images/UI/Info_03.bmp");
	IMG_MGR->OpenImg("Images/UI/Type_01.bmp");

	auto	typeImg = IMG_MGR->GetImg("Type_01");
	if (typeImg != nullptr)
	{
		typeImg->SetTrans();
		typeImg->SetFrame(18);
	}

	//	리포트
	IMG_MGR->OpenImg("Images/UI/Dialog_01.bmp");
	IMG_MGR->OpenImg("Images/UI/SaveBox1.bmp");
	IMG_MGR->OpenImg("Images/UI/SaveBox2.bmp");
	auto	dialogImg = IMG_MGR->GetImg("Dialog_01");
	if (dialogImg != nullptr)
	{
		dialogImg->SetTrans();
	}
	auto	saveImg1 = IMG_MGR->GetImg("SaveBox1");
	if (saveImg1 != nullptr)
	{
		saveImg1->SetTrans();
	}
	auto	saveImg2 = IMG_MGR->GetImg("SaveBox2");
	if (saveImg2 != nullptr)
	{
		saveImg2->SetTrans();
	}

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
	IMG_MGR->OpenImg("Images/SB/SB01_01.bmp");
	IMG_MGR->OpenImg("Images/SB/SB01_02.bmp");
	IMG_MGR->OpenImg("Images/SB/SB02_01.bmp");
	IMG_MGR->OpenImg("Images/SB/SB02_02.bmp");
	IMG_MGR->OpenImg("Images/SB/SB03_01.bmp");
	IMG_MGR->OpenImg("Images/SB/SB03_02.bmp");
	IMG_MGR->GetImg("SB02_02")->SetTrans(true, TRANS_COLOR);
	IMG_MGR->GetImg("SB02_01")->SetTrans(true, TRANS_COLOR);

	//	사전
	IMG_MGR->OpenImg("Images/UI/Dic_01.bmp");
	IMG_MGR->OpenImg("Images/UI/Dic_02.bmp");
	auto dic = IMG_MGR->GetImg("Dic_02");
	if (dic != nullptr)
	{
		dic->SetTrans();
		dic->SetFrame(2);
	}

	//	배틀
	IMG_MGR->OpenImg("Images/UI/Battle_bg.bmp");		//	배경
	IMG_MGR->OpenImg("Images/UI/Battle_grass.bmp");		//	배경
	IMG_MGR->OpenImg("Images/UI/Dialog_02.bmp");		//	대화창
	IMG_MGR->OpenImg("Images/UI/BattleInfo_01.bmp");		//	대화창
	IMG_MGR->OpenImg("Images/UI/BattleInfo_02.bmp");		//	대화창
	IMG_MGR->OpenImg("Images/UI/Player.bmp");
	IMG_MGR->OpenImg("Images/UI/ThrowBall.bmp");
	auto	field = IMG_MGR->GetImg("Battle_grass");
	if (field != nullptr)
	{
		field->SetTrans();
	}
	auto	myInfo = IMG_MGR->GetImg("BattleInfo_01");
	if (myInfo != nullptr)
	{
		myInfo->SetTrans();
		myInfo->SetFrame(2);
	}
	auto	enemyInfo = IMG_MGR->GetImg("BattleInfo_02");
	if (enemyInfo != nullptr)
	{
		enemyInfo->SetTrans();
	}
	auto	playerImg = IMG_MGR->GetImg("Player");
	if (playerImg != nullptr)
	{
		playerImg->SetTrans();
		playerImg->SetFrame(5);
	}
	auto	ballImg = IMG_MGR->GetImg("ThrowBall");
	if (ballImg != nullptr)
	{
		ballImg->SetTrans();
		ballImg->SetFrame(9);
	}

	//트레이너
	IMG_MGR->OpenImg("Images/UI/TrainerCard.bmp");
	IMG_MGR->OpenImg("Images/UI/League.bmp");

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
