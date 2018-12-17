#include "stdafx.h"
#include "Scene_Info.h"
#include "SceneMgr.h"


Scene_Info::Scene_Info()
{
}


Scene_Info::~Scene_Info()
{
}

void Scene_Info::Init(HWND _hWnd)
{
}

void Scene_Info::Update(float _elapseTime)
{
}

void Scene_Info::Render(HDC _hdc)
{
	switch (m_InfoPage)
	{
	case 0:		//	포켓몬 정보
	{
		auto	backgroundImg = IMG_MGR->GetImg("Info_01");
		backgroundImg->Render(_hdc);
		
		std::stringstream	buf;
		
		buf << m_Lv[m_NowPokemon];
		m_Txt.TextBox(_hdc, 60, 80, buf.str().c_str(), 40, WHITE);

		buf.str("");
		buf << m_Name[m_NowPokemon];
		m_Txt.TextBox(_hdc, 200, 80, buf.str().c_str(), 40, WHITE);
		m_Txt.TextBox(_hdc, 670, 140, buf.str().c_str(), 40);

		buf.str("");
		buf << m_DicNumber[m_NowPokemon];
		m_Txt.TextBox(_hdc, 670, 84, buf.str().c_str(), 40);
		
		buf.str("");
		buf << m_Type[m_NowPokemon];
		m_Txt.TextBox(_hdc, 670, 194, buf.str().c_str(), 40);

		buf.str("");
		buf << m_Father;
		m_Txt.TextBox(_hdc, 670, 244, buf.str().c_str(), 40);

		buf.str("");
		buf << m_Num;
		m_Txt.TextBox(_hdc, 670, 294, buf.str().c_str(), 40);

		buf.str("");
		buf << m_Poket[m_NowPokemon];
		m_Txt.TextBox(_hdc, 580, 394, buf.str().c_str(), 40);

	}break;

	case 1:		//	포켓몬 능력
	{
		auto	backgroundImg = IMG_MGR->GetImg("Info_02");
		backgroundImg->Render(_hdc);

		std::stringstream	buf;

		buf << m_Lv[m_NowPokemon];
		m_Txt.TextBox(_hdc, 60, 80, buf.str().c_str(), 40, WHITE);

		buf.str("");
		buf << m_Name[m_NowPokemon];
		m_Txt.TextBox(_hdc, 200, 80, buf.str().c_str(), 40, WHITE);

		buf.str("");
		buf << m_HpNow[m_NowPokemon];
		m_Txt.TextBox(_hdc, 720, 84, buf.str().c_str(), 40);

		buf.str("");
		buf << m_HpAll[m_NowPokemon];
		m_Txt.TextBox(_hdc, 835, 84, buf.str().c_str(), 40);
				
		buf.str("");
		buf << m_Atk[m_NowPokemon];
		m_Txt.TextBox(_hdc, 835, 158, buf.str().c_str(), 40);

		buf.str("");
		buf << m_Def[m_NowPokemon];
		m_Txt.TextBox(_hdc, 835, 208, buf.str().c_str(), 40);

		buf.str("");
		buf << m_sAtk[m_NowPokemon];
		m_Txt.TextBox(_hdc, 835, 262, buf.str().c_str(), 40);

		buf.str("");
		buf << m_sDef[m_NowPokemon];
		m_Txt.TextBox(_hdc, 835, 312, buf.str().c_str(), 40);

		buf.str("");
		buf << m_Speed[m_NowPokemon];
		m_Txt.TextBox(_hdc, 835, 364, buf.str().c_str(), 40);

		buf.str("");
		buf << m_ExpNow[m_NowPokemon];
		m_Txt.TextBox(_hdc, 720, 420, buf.str().c_str(), 40);

		buf.str("");
		buf << (m_ExpAll[m_NowPokemon] - m_ExpNow[m_NowPokemon]);
		m_Txt.TextBox(_hdc, 720, 470, buf.str().c_str(), 40);

		buf.str("");
		buf << m_Special[m_NowPokemon];
		m_Txt.TextBox(_hdc, 200, 534, buf.str().c_str(), 40);
	}break;

	case 2:		//	싸울 기술
	{
		auto	backgroundImg = IMG_MGR->GetImg("Info_03");
		auto	typeImg = IMG_MGR->GetImg("Type_01");
		backgroundImg->Render(_hdc);

		std::stringstream	buf;

		buf << m_Lv[m_NowPokemon];
		m_Txt.TextBox(_hdc, 60, 80, buf.str().c_str(), 40, WHITE);

		buf.str("");
		buf << m_Name[m_NowPokemon];
		m_Txt.TextBox(_hdc, 200, 80, buf.str().c_str(), 40, WHITE);

		buf.str("");
		typeImg->AniRender(_hdc, m_AtkType1[m_NowPokemon], 492, 84);
		buf << m_AtkList1[m_NowPokemon];
		m_Txt.TextBox(_hdc, 646, 84, buf.str().c_str(), 40);
		buf.str("pp");
		m_Txt.TextBox(_hdc, 726, 138, buf.str().c_str(), 36);
		buf.str("");
		buf << m_PpNowList1[m_NowPokemon] << " / " << m_PpAllList1[m_NowPokemon];
		m_Txt.TextBox(_hdc, 770, 140, buf.str().c_str(), 40);
		
		buf.str("");
		typeImg->AniRender(_hdc, m_AtkType2[m_NowPokemon], 492, 196);
		buf << m_AtkList2[m_NowPokemon];
		m_Txt.TextBox(_hdc, 646, 196, buf.str().c_str(), 40);
		buf.str("pp");
		m_Txt.TextBox(_hdc, 726, 250, buf.str().c_str(), 36);
		buf.str("");
		buf << m_PpNowList2[m_NowPokemon] << " / " << m_PpAllList2[m_NowPokemon];
		m_Txt.TextBox(_hdc, 770, 252, buf.str().c_str(), 40);
		
		buf.str("");
		typeImg->AniRender(_hdc, m_AtkType3[m_NowPokemon], 492, 308);
		buf << m_AtkList3[m_NowPokemon];
		m_Txt.TextBox(_hdc, 646, 308, buf.str().c_str(), 40);
		buf.str("pp");
		m_Txt.TextBox(_hdc, 726, 362, buf.str().c_str(), 36);
		buf.str("");
		buf << m_PpNowList3[m_NowPokemon] << " / " << m_PpAllList3[m_NowPokemon];
		m_Txt.TextBox(_hdc, 770, 364, buf.str().c_str(), 40);
		
		buf.str("");
		typeImg->AniRender(_hdc, m_AtkType4[m_NowPokemon], 492, 420);
		buf << m_AtkList4[m_NowPokemon];
		m_Txt.TextBox(_hdc, 646, 420, buf.str().c_str(), 40);
		buf.str("pp");
		m_Txt.TextBox(_hdc, 726, 474, buf.str().c_str(), 36);
		buf.str("");
		buf << m_PpNowList4[m_NowPokemon] << " / " << m_PpAllList4[m_NowPokemon];
		m_Txt.TextBox(_hdc, 770, 476, buf.str().c_str(), 40);

	}break;
	}
}

bool Scene_Info::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case VK_UP:
		{
			m_NowPokemon--;
			if (m_NowPokemon < 0)
				m_NowPokemon = 0;
		}break;

		case VK_DOWN:
		{
			m_NowPokemon++;
			if (m_NowPokemon > 3)
				m_NowPokemon = 3;
		}break;

		case VK_LEFT:
		{
			m_InfoPage--;
			if (m_InfoPage < 0)
				m_InfoPage = 0;
		}break;

		case VK_RIGHT:
		{
			m_InfoPage++;
			if (m_InfoPage > 2)
				m_InfoPage = 2;
		}break;

		case 'x':
		case 'X': {	SCENE_MGR.SetScene(SCENE_POKEMON); }break;

		case VK_ESCAPE: return true;	break;
		}
	}break;

	}
	return false;
}
