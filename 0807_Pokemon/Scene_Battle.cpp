#include "stdafx.h"
#include "Scene_Battle.h"
#include "SceneMgr.h"
#include "PokemonManager.h"

Scene_Battle::Scene_Battle()
{
	m_BGDC = IMG_MGR->GetImg("Battle_bg")->GetImgDC();
	m_BGDC1 = IMG_MGR->GetImg("Dialog_02")->GetImgDC();
}

Scene_Battle::~Scene_Battle()
{
}

void Scene_Battle::Init(HWND _hWnd)
{
}

void Scene_Battle::Update(float _elapseTime)
{
	m_time += _elapseTime;
	m_ballTime += _elapseTime;

	if (0.1f <= m_ballTime)
	{
		m_ballTime -= 0.1f;
		if (m_playerAni > 2)
			m_ballAni++;
	}
	if (0.3f <= m_time)
	{
		m_time -= 0.3f;
		m_Ani++;
		
		if (m_Ani > 1)
		{
			m_Ani = 0;
		}

		if (m_playerAni > 0 && m_playerAni < 4)
			m_playerAni++;
	}
	
	if (m_Type == INTRO && i < 2)
	{
		//	포켓몬 밑 잔디 등장
		if (m_EnemyMove < 448)
			m_EnemyMove += 8;
		else if(m_EnemyMove > 448)
			m_EnemyMove = 448;

		if (m_MyMove > 0)
			m_MyMove -= 8;
		else if(m_MyMove < 0)
			m_MyMove = 0;

		//	적 체력 출력
		if (m_EnemyMove == 448)
		{
			if (m_EnemyInfo < 52)
				m_EnemyInfo += 16;
			else if (m_EnemyInfo > 52)
				m_EnemyInfo = 52;
		}
	}
	else if (m_Type == INTRO && i >= 2)
	{
		if (m_playerExit > -450)
			m_playerExit -= 8;
		else if (m_playerExit < -450)
			m_playerExit = -450;
	}

}

void Scene_Battle::Render(HDC _hdc)
{
	auto	field1 = IMG_MGR->GetImg("Battle_grass");
	auto	field2 = field1;
	auto	myInfo = IMG_MGR->GetImg("BattleInfo_01");
	auto	enemyInfo = IMG_MGR->GetImg("BattleInfo_02");
	auto	playerImg = IMG_MGR->GetImg("Player");
	auto	ballImg = IMG_MGR->GetImg("ThrowBall");

	//	배경
	BitBlt(_hdc, 0, 0, WIN_WIDTH, 448, m_BGDC, 0, 0, SRCCOPY);		
	//	잔디
	field1->AniRender(_hdc, 0, m_EnemyMove, 184);
	field2->AniRender(_hdc, 0, m_MyMove, 392);
	//	플레이어
	playerImg->AniRender(_hdc, m_playerAni, m_MyMove + 192 + m_playerExit, 192);
	//	몬스터볼
	if(m_playerAni >= 3)
		ballImg->AniRender(_hdc, m_ballAni, 192, 192);
	//	대사창
	BitBlt(_hdc, 0, 448, WIN_WIDTH, 192, m_BGDC1, 0, 0, SRCCOPY);	
	//	체력창
	enemyInfo->AniRender(_hdc, 0, m_EnemyInfo, 64);
	//myInfo->AniRender(_hdc, m_Ani, 504, 296);
	

	std::stringstream	buf_1;
	std::stringstream	buf_2;
	
	switch (m_Type)
	{
	case INTRO:
	{
		switch (i)
		{
		case 0:
		{
			buf_1 << "앗! 야생의";
			buf_2 << "몬스터이름" << "(이)가";
		}break;
		case 1:
		{
			buf_1 << "몬스터이름" << "(이)가";
			buf_2 << "튀어나왔다!";
		}break;
		case 2:
		{
			buf_1 << "가랏! " << "포켓몬 이름";
			buf_2 << "";
		}break;
		default:
		{
			buf_1 << "포켓몬 이름" << "는(은)";
			buf_2 << "무엇을 할까?";
			m_Type = BATTLE;
			i = 0;
		}break;
		}
	}break;
	case BATTLE:
	{
		switch (i)
		{
		case 0:
		{
			buf_1 << "포켓몬 이름" << "는(은)";
			buf_2 << "무엇을 할까?";
		}break;
		case 1:
		{
			buf_1 << "몬스터이름" << "의";
			buf_2 << "기술이름" << "공격!";
			m_Type = REACTION;
		}break;
		case 2:
		{
			buf_1 << "상대포켓몬이름" << "의";
			buf_2 << "기술이름" << "공격!";
			m_Type = REACTION;
		}break;
		default:
		{
			
		}break;
		}
	}break;
	case REACTION:
	{
		switch (m_Reaction)
		{
		case REACTION_CRITICAL:
		{
		}break;
		case REACTION_GOOD:
		{
		}break;
		case REACTION_NORMAL:
		{
		}break;
		case REACTION_BAD:
		{
		}break;
		case REACTION_NO:
		{
		}break;
		}
	}break;

	case ENDBATTLE:
	{

	}break;
	}
	
	
	m_Txt.TextBox(_hdc, 50, 490, buf_1.str().c_str(), 40, WHITE);
	m_Txt.TextBox(_hdc, 50, 550, buf_2.str().c_str(), 40, WHITE);
}

bool Scene_Battle::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case 'z':
		case 'Z': 
		{	
			//인트로에 i == 1일때
			if (m_Type == INTRO && i == 1)
				m_playerAni = 1;
			i++;
		}break;

		case 'x':
		case 'X': {	SCENE_MGR.SetScene(SCENE_MENU); }break;

		case 'b':
		case 'B': {	SCENE_MGR.SetScene(SCENE_MAIN); }break;

		case VK_ESCAPE: return true;	break;
		}
	}break;

	}
	return false;
}