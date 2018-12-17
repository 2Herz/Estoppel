#include "stdafx.h"
#include "PlayerManager.h"
#include "Pokemon.h"

PlayerManager::PlayerManager()
{
	m_sex = MALE;
	m_name = "ทนตๅ";
	m_badgeCount = 0;
	m_animationTime = 0.0f;
	m_step = STEP::NO_FEET;
	m_prevStep = STEP::R_FEET;
	m_currentPosition = {7,5};
}

PlayerManager::~PlayerManager()
{
	Release();
}

void PlayerManager::GoUp()
{
	if (m_prevStep == STEP::L_FEET)
	{
		m_step = STEP::R_FEET;
		m_prevStep = STEP::R_FEET;
	}
	else
	{
		m_step = STEP::L_FEET;
		m_prevStep = STEP::L_FEET;
	}
	m_currentPosition.y--;
	m_isMoving = true;
}

void PlayerManager::GoDown()
{
	if (m_prevStep == STEP::L_FEET)
	{
		m_step = STEP::R_FEET;
		m_prevStep = STEP::R_FEET;
	}
	else
	{
		m_step = STEP::L_FEET;
		m_prevStep = STEP::L_FEET;
	}
	m_currentPosition.y++;
	m_isMoving = true;
}

void PlayerManager::GoLeft()
{
	if (m_prevStep == STEP::L_FEET)
	{
		m_step = STEP::R_FEET;
		m_prevStep = STEP::R_FEET;
	}
	else
	{
		m_step = STEP::L_FEET;
		m_prevStep = STEP::L_FEET;
	}
	m_currentPosition.x--;
	m_isMoving = true;
}

void PlayerManager::GoRight()
{
	if (m_prevStep == STEP::L_FEET)
	{
		m_step = STEP::R_FEET;
		m_prevStep = STEP::R_FEET;
	}
	else
	{
		m_step = STEP::L_FEET;
		m_prevStep = STEP::L_FEET;
	}
	m_currentPosition.x++;
	m_isMoving = true;
}

void PlayerManager::Init(HWND _hWnd)
{
	m_image.LoadImg(_hWnd, "Images/player.bmp");
	m_image.SetFrame(12,3);
	m_image.SetTrans(true, TRANS_COLOR);
}

void PlayerManager::Release()
{
}

std::string PlayerManager::GetName()
{
	return m_name;
}

void PlayerManager::SetName(std::string _name)
{
	m_name = _name;
}

bool PlayerManager::GetSex()
{
	return m_sex;
}

void PlayerManager::SetSex(bool _sex)
{
	m_sex = _sex;
}

short PlayerManager::GetBadgeCount()
{
	return m_badgeCount;
}

void PlayerManager::IncreaseBadge()
{
	if (m_badgeCount != 8)
	{
		m_badgeCount++;
	}
}

int PlayerManager::GetMoney()
{
	return m_money;
}

void PlayerManager::SetMoney(int _money)
{
	m_money = _money;
}

void PlayerManager::Update(float _elapseTime)
{
	m_animationTime += _elapseTime;

	if (m_animationTime >= TIMER.GetTimeUnit() )
	{
		m_animationTime -= TIMER.GetTimeUnit();
	}
	else if (m_animationTime >= TIMER.GetTimeUnit()/2)
	{
		m_step = STEP::NO_FEET;
	}
}

void PlayerManager::Render(HDC _hdc)
{
	int xPos = (WIN_WIDTH / 2) - 40;
	int yPos = (WIN_HEIGHT / 2) + MAP_TILE_SIZE - HERO_HEIGHT;

	short xPoint = m_direction + (4 * m_step);

	m_image.AniRenderXY(_hdc, xPoint, m_state, xPos, yPos);
}

void PlayerManager::SetDirection(short _direction)
{
	m_direction = _direction;
	switch (_direction)
	{
	case DIRECTION::UP:
	{
		if (!NPC_MANAGER.CheckNPCPosition({ m_currentPosition.x , m_currentPosition.y - 1 }))
		{
			GoUp();
			MAP_MANAGER.MoveUp();
			m_isMoving = true;
		}
	}break;
	case DIRECTION::DOWN:
	{
		if (!NPC_MANAGER.CheckNPCPosition({ m_currentPosition.x , m_currentPosition.y + 1 }))
		{
			GoDown();
			MAP_MANAGER.MoveDown();
			m_isMoving = true;
		}
	}break;
	case DIRECTION::LEFT:
	{
		if (!NPC_MANAGER.CheckNPCPosition({ m_currentPosition.x - 1, m_currentPosition.y }))
		{
			GoLeft();
			MAP_MANAGER.MoveLeft();
			m_isMoving = true;
		}
	}break;
	case DIRECTION::RIGHT:
	{
		if (!NPC_MANAGER.CheckNPCPosition({ m_currentPosition.x + 1, m_currentPosition.y }))
		{
			GoRight();
			MAP_MANAGER.MoveRight();
			m_isMoving = true;
		}
	}break;
	}
}

bool PlayerManager::isMoving()
{
	return m_isMoving;
}

void PlayerManager::SetIsMoving(bool _isMoving)
{
	m_isMoving = _isMoving;
}

void PlayerManager::SetPlayerState(short _state)
{
	m_state = _state;
}

short PlayerManager::GetPlayerState()
{
	return m_state;
}

POINT PlayerManager::GetPosition()
{
	return m_currentPosition;
}

void PlayerManager::SetPosition(POINT _position)
{
	m_currentPosition = _position;
}

bool PlayerManager::IsControlActivated()
{
	return m_controlActivated;
}
