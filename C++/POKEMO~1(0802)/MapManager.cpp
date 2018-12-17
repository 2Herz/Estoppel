#include "stdafx.h"
#include "MapManager.h"

MapManager::MapManager()
{
}

MapManager::~MapManager()
{
}

void MapManager::MoveUp()
{
	m_xOffset = 0;
	m_yOffset = -MAP_TILE_SIZE;
}

void MapManager::MoveDown()
{
	m_xOffset = 0;
	m_yOffset = MAP_TILE_SIZE;
}

void MapManager::MoveLeft()
{
	m_xOffset = -MAP_TILE_SIZE;
	m_yOffset = 0;
}

void MapManager::MoveRight()
{
	m_xOffset = MAP_TILE_SIZE;
	m_yOffset = 0;
}

void MapManager::ToggleGrid()
{
	m_gridMode = !m_gridMode;
}

void MapManager::DrawGrid(HDC _hdc)
{
	if (m_gridMode)
	{
		int xMax = WIN_WIDTH / MAP_TILE_SIZE;
		int yMax = WIN_HEIGHT / MAP_TILE_SIZE;

		for (int y = 0; y <= yMax; y++)
		{
			MoveToEx(_hdc, 0, y * MAP_TILE_SIZE, nullptr);
			LineTo(_hdc, WIN_WIDTH, y * MAP_TILE_SIZE);
		}
		for (int x = 0; x <= xMax; x++)
		{
			MoveToEx(_hdc, x * MAP_TILE_SIZE, 0, nullptr);
			LineTo(_hdc, x * MAP_TILE_SIZE, WIN_HEIGHT);
		}
	}
}

POINT MapManager::GetCamPosition()
{
	return m_camPosition;
}

void MapManager::SetCamPosition(int _x, int _y)
{
	m_camPosition.x = _x;
	m_camPosition.y = _y;
}

void MapManager::Update(float _elapseTime)
{
	m_elapseTime += _elapseTime;
	float value = m_elapseTime / TIMER.GetTimeUnit();

	if (m_elapseTime >= TIMER.GetTimeUnit())
	{
		m_elapseTime -= TIMER.GetTimeUnit();
	}

	if (value >= 1.0f)
	{
		PLAYER_MANAGER.SetIsMoving(false);
		SetCamPosition(m_prevCamPosition.x + m_xOffset, m_prevCamPosition.y + m_yOffset);
		m_prevCamPosition = m_camPosition;
		m_xOffset = 0;
		m_yOffset = 0;
	}
	else
	{
		SetCamPosition(m_prevCamPosition.x + (value * m_xOffset), m_prevCamPosition.y + (value * m_yOffset));
	}
}


