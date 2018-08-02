#include "stdafx.h"
#include "Scene_Main.h"


Scene_Main::Scene_Main()
{
}


Scene_Main::~Scene_Main()
{
}

void Scene_Main::Init(HWND _hWnd)
{
}

void Scene_Main::Update(float _elapseTime)
{
	NPC_MANAGER.Update(_elapseTime);

	if (PLAYER_MANAGER.isMoving())
	{
		PLAYER_MANAGER.Update(_elapseTime);
		MAP_MANAGER.Update(_elapseTime);
	}

	//상하좌우 이동
	if (KEY_MANAGER.StayKeyDown(VK_UP))
	{
		if (!PLAYER_MANAGER.isMoving())
		{
			PLAYER_MANAGER.SetDirection(DIRECTION::UP);
		}
	}
	if (KEY_MANAGER.StayKeyDown(VK_DOWN))
	{
		if (!PLAYER_MANAGER.isMoving())
		{
			PLAYER_MANAGER.SetDirection(DIRECTION::DOWN);
		}
	}
	if (KEY_MANAGER.StayKeyDown(VK_LEFT))
	{
		if (!PLAYER_MANAGER.isMoving())
		{
			PLAYER_MANAGER.SetDirection(DIRECTION::LEFT);
		}
	}
	if (KEY_MANAGER.StayKeyDown(VK_RIGHT))
	{
		if (!PLAYER_MANAGER.isMoving())
		{
			PLAYER_MANAGER.SetDirection(DIRECTION::RIGHT);
		}
	}

	// 달리기
	if (KEY_MANAGER.StayKeyDown('X'))
	{
		if (!PLAYER_MANAGER.isMoving())
		{
			PLAYER_MANAGER.SetPlayerState(PLAYER_STATE::RUN);
			TIMER.SetTimeUnit(0.25f);
		}
	}
	// 자전거 타기/내리기
	else if (KEY_MANAGER.IsToggleKey('Z'))
	{
		PLAYER_MANAGER.SetPlayerState(PLAYER_STATE::RIDE_BIKE);
		TIMER.SetTimeUnit(0.2f);
	}
	else
	{
		if (!PLAYER_MANAGER.isMoving())
		{
			PLAYER_MANAGER.SetPlayerState(PLAYER_STATE::WALK);
			TIMER.SetTimeUnit(0.5f);
		}
	}

	if (KEY_MANAGER.OnceKeyUp('X'))
	{
		PLAYER_MANAGER.SetPlayerState(PLAYER_STATE::WALK);
		TIMER.SetTimeUnit(0.5f);
	}
}

void Scene_Main::Render(HDC _hdc)
{
	NPC_MANAGER.AreaRender(_hdc);
	MAP_MANAGER.DrawGrid(_hdc);

	int halfW = WIN_WIDTH / 2;
	int halfH = WIN_HEIGHT / 2;

	NPC_MANAGER.Render(_hdc);
	PLAYER_MANAGER.Render(_hdc);
	
	TIMER.Render(_hdc, 0, 0);
	std::stringstream cam;
	POINT camPos = MAP_MANAGER.GetCamPosition();
	cam << camPos.x << ", " << camPos.y;
	TextOut(_hdc, 0, 30, cam.str().c_str(), cam.str().length());

	cam.str("");
	Skill testSkill = SKILL_MANAGER.GetSkill(0);
	cam << testSkill.m_name << " - 위력 : " << testSkill.m_damage << ", 명중률 : " << testSkill.m_accuracy;
	TextOut(_hdc, 0, 50, cam.str().c_str(), cam.str().length());

	cam.str("");
	cam << "player pos : " << PLAYER_MANAGER.GetPosition().x << ", " << PLAYER_MANAGER.GetPosition().y;
	TextOut(_hdc, 0, 70, cam.str().c_str(), cam.str().length());

	cam.str("");
	cam << POKEDEX.GetPokemonData(2).m_name << ", " << POKEDEX.GetPokemonData(2).m_type_1;
	TextOut(_hdc, 0, 90, cam.str().c_str(), cam.str().length());

	TextOut(_hdc, g_mousePos.x, g_mousePos.y, g_posStr.str().c_str(), g_posStr.str().length());
}

bool Scene_Main::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_MOUSEMOVE:
	{
		g_mousePos.x = GET_X_LPARAM(_lParam);
		g_mousePos.y = GET_Y_LPARAM(_lParam);
		int posX = (MAP_MANAGER.GetCamPosition().x + g_mousePos.x) / MAP_TILE_SIZE;
		int posY = (MAP_MANAGER.GetCamPosition().y + g_mousePos.y) / MAP_TILE_SIZE;

		g_posStr.str("");
		g_posStr << posX << ", " << posY;
	}break;

	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case 'u':
		case 'U': {MAP_MANAGER.ToggleGrid(); }break;
		
		case 'i':
		case 'I': {NPC_MANAGER.SwitchAreaRender(); }break;

		case VK_RETURN:	{SCENE_MGR.SetScene(SCENE_MENU); }break;

		case VK_ESCAPE: {PostQuitMessage(0); }break;
		}
	}break;

	}
	return false;
}
