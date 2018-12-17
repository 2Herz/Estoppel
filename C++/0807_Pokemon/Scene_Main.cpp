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

	if (PLAYER_MANAGER.IsControlActivated())
	{
		//상하좌우 이동
		if (KEY_MANAGER.StayKeyDown(VK_UP))
		{
			if (PLAYER_MANAGER.GetPosition().y > 0)
			{
				if (!PLAYER_MANAGER.isMoving())
				{
					PLAYER_MANAGER.SetDirection(DIRECTION::UP);
				}
			}
			else
			{

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
			if (PLAYER_MANAGER.GetPosition().x > 0)
			{
				if (!PLAYER_MANAGER.isMoving())
				{
					PLAYER_MANAGER.SetDirection(DIRECTION::LEFT);
				}
			}
			else
			{

			}
		}
		if (KEY_MANAGER.StayKeyDown(VK_RIGHT))
		{
			if (!PLAYER_MANAGER.isMoving())
			{
				PLAYER_MANAGER.SetDirection(DIRECTION::RIGHT);
			}
		}

		if (!PLAYER_MANAGER.isMoving())
		{
			// 자전거 타기/내리기
			if (KEY_MANAGER.OnceKeyDown('C'))
			{
				if (!m_rideBike)
				{
					PLAYER_MANAGER.SetPlayerState(PLAYER_STATE::RIDE_BIKE);
					TIMER.SetTimeUnit(0.2f);
					m_rideBike = true;
				}
				else
				{
					m_rideBike = false;
				}
			}
			// 달리기
			else if (KEY_MANAGER.StayKeyDown('X'))
			{
				PLAYER_MANAGER.SetPlayerState(PLAYER_STATE::RUN);
				TIMER.SetTimeUnit(0.25f);
			}
			else
			{
				if (!m_rideBike)
				{
					PLAYER_MANAGER.SetPlayerState(PLAYER_STATE::WALK);
					TIMER.SetTimeUnit(0.5f);
				}
			}
		}
	}
}

bool b = true;
void Scene_Main::Render(HDC _hdc)
{
	MAP_MANAGER.Render(_hdc);
	NPC_MANAGER.AreaRender(_hdc);
	MAP_MANAGER.DrawGrid(_hdc);
	

	int halfW = WIN_WIDTH / 2;
	int halfH = WIN_HEIGHT / 2;

	NPC_MANAGER.Render(_hdc);
	PLAYER_MANAGER.Render(_hdc);
	
	/////////////////////////////////
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

	cam.str("");
	if (b)
	{
		POKEMON_MANAGER.GeneratePokemon(0);
		b = false;
	}
	Pokemon * tempPoke = POKEMON_MANAGER.GetWildPokemon();
	cam << tempPoke->m_data.m_name << " - " << tempPoke->m_skill[0].m_name
		<< " , " << tempPoke->m_skill[1].m_name
		<< " , " << tempPoke->m_skill[2].m_name
		<< " , " << tempPoke->m_skill[3].m_name;
	TextOut(_hdc, 0, 110, cam.str().c_str(), cam.str().length());

	TextOut(_hdc, m_mousePos.x, m_mousePos.y, m_posStr.str().c_str(), m_posStr.str().length());
}

bool Scene_Main::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_MOUSEMOVE:
	{
		m_mousePos.x = GET_X_LPARAM(_lParam);
		m_mousePos.y = GET_Y_LPARAM(_lParam);
		int posX = (MAP_MANAGER.GetCamPosition().x + m_mousePos.x) / MAP_TILE_SIZE;
		int posY = (MAP_MANAGER.GetCamPosition().y + m_mousePos.y) / MAP_TILE_SIZE;

		m_posStr.str("");
		m_posStr << posX << ", " << posY;
	}break;

	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case 'u':
		case 'U': {MAP_MANAGER.ToggleGrid(); }break;

		case 'i':
		case 'I': {NPC_MANAGER.SwitchAreaRender(); }break;

		case 'b':
		case 'B': {SCENE_MGR.SetScene(SCENE_BATTLE); }break;

		case VK_RETURN:
		{
			if (PLAYER_MANAGER.IsControlActivated())
			{
				SCENE_MGR.SetScreen(GetDC(_hWnd));
				SCENE_MGR.SetScene(SCENE_MENU);
			}
		}break;

		case VK_ESCAPE: {PostQuitMessage(0); }break;
		}
	}break;

	}
	return false;
}
