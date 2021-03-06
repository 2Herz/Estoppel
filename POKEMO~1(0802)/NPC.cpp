#include "stdafx.h"
#include "NPC.h"

NPC::NPC()
{
}

NPC::~NPC()
{
}

NPC::NPC(int _number, int _mapNumber, int _function, int _direction, int _pattern, int _searchDistance, POINT _position, SIZE _moveBoxSize)
{
	m_number = _number;
	m_function = _function;
	m_searchDistance = _searchDistance;
	m_direction = _direction;
	m_mapNumber = _mapNumber;

	m_step = STEP::R_FEET;
	m_position = _position;
	m_prevPosition = _position;
	m_rootPosition.x = _position.x * MAP_TILE_SIZE;
	m_rootPosition.y = _position.y * MAP_TILE_SIZE;
	m_realPosition.x = _position.x * MAP_TILE_SIZE;
	m_realPosition.y = _position.y * MAP_TILE_SIZE;
	m_moveBox = _moveBoxSize;
	m_moveBoxPosition = { 0,0 };
	m_state = NPC_STATE::NPC_NORMAL;
	m_pattern = _pattern;
	m_animationTime = 0.0f;
}

void NPC::GoLeft()
{
	POINT playerPos = PLAYER_MANAGER.GetPosition();
	if (playerPos.x != m_position.x - 1 || playerPos.y != m_position.y)
	{
		if (m_step == STEP::L_FEET)
		{
			m_step = STEP::R_FEET;
		}
		else
		{
			m_step = STEP::L_FEET;
		}
		m_isMoving = true;
		m_position.x--;
		m_moveBoxPosition.x--;
	}
}

void NPC::GoRight()
{
	POINT playerPos = PLAYER_MANAGER.GetPosition();
	if (playerPos.x != m_position.x + 1 || playerPos.y != m_position.y)
	{
		if (m_step == STEP::L_FEET)
		{
			m_step = STEP::R_FEET;
		}
		else
		{
			m_step = STEP::L_FEET;
		}
		m_isMoving = true;
		m_position.x++;
		m_moveBoxPosition.x++;
	}
}

void NPC::GoUp()
{
	POINT playerPos = PLAYER_MANAGER.GetPosition();
	if (playerPos.x != m_position.x || playerPos.y != m_position.y - 1)
	{
		if (m_step == STEP::L_FEET)
		{
			m_step = STEP::R_FEET;
		}
		else
		{
			m_step = STEP::L_FEET;
		}
		m_isMoving = true;
		m_position.y--;
		m_moveBoxPosition.y--;
	}
}

void NPC::GoDown()
{
	POINT playerPos = PLAYER_MANAGER.GetPosition();
	if (playerPos.x != m_position.x || playerPos.y != m_position.y + 1)
	{
		if (m_step == STEP::L_FEET)
		{
			m_step = STEP::R_FEET;
		}
		else
		{
			m_step = STEP::L_FEET;
		}
		m_isMoving = true;
		m_position.y++;
		m_moveBoxPosition.y++;
	}
}

void NPC::TurnUp()
{
	m_direction = DIRECTION::UP;
}

void NPC::TurnDown()
{
	m_direction = DIRECTION::DOWN;
}

void NPC::TurnLeft()
{
	m_direction = DIRECTION::LEFT;
}

void NPC::TurnRight()
{
	m_direction = DIRECTION::RIGHT;
}

void NPC::DoPattern()
{
	m_prevPosition = m_position;

	switch (m_pattern)
	{

	//한방향 주시
	case NPC_PATTERN::STARRING:
	{
		switch (m_direction)
		{
		case DIRECTION::UP:
		{
			//위방향 이미지 출력
		}break;

		case DIRECTION::DOWN:
		{
			//아래방향 이미지 출력
		}break;

		case DIRECTION::LEFT:
		{
			//왼방향 이미지 출력
		}break;

		case DIRECTION::RIGHT:
		{
			//오른방향 이미지 출력
		}break;
		}
	}break;

	//시계방향 배회
	case NPC_PATTERN::TURN_ARROUND_CLOCKWISE:
	{
		switch (m_direction)
		{
		case DIRECTION::UP:
		{
			if (m_moveBoxPosition.y > 0)
			{
				GoUp();
			}
			else
			{
				//가로 행동반경이 폭이 1일때는 바로 아래로
				if (m_moveBox.cx == 1)
				{
					TurnDown();
				}
				//1이 아니라면 오른쪽으로
				else
				{
					TurnRight();
					GoRight();
				}
			}
		}break;

		case DIRECTION::DOWN:
		{
			if (m_moveBoxPosition.y < m_moveBox.cy - 1)
			{
				GoDown();
			}
			else
			{
				//가로 행동반경이 폭이 1일때는 바로 위로
				if (m_moveBox.cx == 1)
				{
					TurnUp();
				}
				//아니라면 왼쪽으로
				else
				{
					TurnLeft();
					GoLeft();
				}
			}
		}break;

		case DIRECTION::LEFT:
		{
			if (m_moveBoxPosition.x > 0)
			{
				GoLeft();
			}
			else
			{
				//세로 행동반경이 폭이 1일때는 바로 오른쪽으로
				if (m_moveBox.cy == 1)
				{
					TurnRight();
				}
				//1이 아니라면 위로이동
				else
				{
					TurnUp();
					GoUp();
				}
			}
		}break;

		case DIRECTION::RIGHT:
		{
			if (m_moveBoxPosition.x < m_moveBox.cx - 1)
			{
				GoRight();
			}
			else
			{
				//세로 행동반경이 폭이 1일때는 바로 왼쪽으로
				if (m_moveBox.cy == 1)
				{
					TurnLeft();
				}
				//1이 아니라면 아래로 이동
				else
				{
					TurnDown();
					GoDown();
				}
			}
		}break;
		}
	}break;

	//반시계방향 배회
	case NPC_PATTERN::TURN_ARROUND_COUNTER_CLOCKWISE:
	{
		switch (m_direction)
		{
		case DIRECTION::UP:
		{
			if (m_moveBoxPosition.y > 0)
			{
				GoUp();
			}
			else
			{
				//가로 행동반경이 폭이 1일때는 바로 아래로
				if (m_moveBox.cx == 1)
				{
					TurnDown();
				}
				//1이 아니라면 왼쪽으로
				else
				{
					TurnLeft();
					GoLeft();
				}
			}
		}break;

		case DIRECTION::DOWN:
		{
			if (m_moveBoxPosition.y < m_moveBox.cy - 1)
			{
				GoDown();
			}
			else
			{
				//가로 행동반경이 폭이 1일때는 바로 위로
				if (m_moveBox.cx == 1)
				{
					TurnUp();
				}
				//아니라면 오른쪽으로
				else
				{
					TurnRight();
					GoRight();
				}
			}
		}break;

		case DIRECTION::LEFT:
		{
			if (m_moveBoxPosition.x > 0)
			{
				GoLeft();
			}
			else
			{
				//세로 행동반경이 폭이 1일때는 바로 오른쪽으로
				if (m_moveBox.cy == 1)
				{
					TurnRight();
				}
				//1이 아니라면 아래로이동
				else
				{
					TurnDown();
					GoDown();
				}
			}
		}break;

		case DIRECTION::RIGHT:
		{
			if (m_moveBoxPosition.x < m_moveBox.cx - 1)
			{
				GoRight();
			}
			else
			{
				//세로 행동반경이 폭이 1일때는 바로 왼쪽으로
				if (m_moveBox.cy == 1)
				{
					TurnLeft();
				}
				//1이 아니라면 위로 이동
				else
				{
					TurnUp();
					GoUp();
				}
			}
		}break;
		}
	}break;

	//빙글빙글
	case NPC_PATTERN::TURNING:
	{
		int direction = rand() % 4;
		switch (direction)
		{
		case DIRECTION::UP:
			TurnUp();
			break;
		case DIRECTION::DOWN:
			TurnDown();
			break;
		case DIRECTION::LEFT:
			TurnLeft();
			break;
		case DIRECTION::RIGHT:
			TurnRight();
			break;
		}
	}break;

	case NPC_PATTERN::RANDOM:
	{
		int direction = rand() % 4;
		switch (direction)
		{
		case DIRECTION::UP:
		{
			if (m_moveBoxPosition.y > 0)
			{
				TurnUp();
				GoUp();
			}
		}break;
		case DIRECTION::DOWN:
		{
			if(m_moveBoxPosition.y < m_moveBox.cy - 1)
			{ 
				TurnDown();
				GoDown();
			}
		}break;
		case DIRECTION::LEFT:
		{
			if (m_moveBoxPosition.x > 0)
			{
				TurnLeft();
				GoLeft();
			}
		}break;
		case DIRECTION::RIGHT:
		{
			if (m_moveBoxPosition.x < m_moveBox.cx - 1)
			{
				TurnRight();
				GoRight();
			}
		}break;
		}
	}break;

	}
	m_realPosition.x = m_position.x * MAP_TILE_SIZE;
	m_realPosition.y = m_position.y * MAP_TILE_SIZE;
}

void NPC::DoScript()
{
	//대화창 UI호출
	//대화창에 대사 출력
	//대화 끝나면 하던일 계속
}

void NPC::DoAction(float _elapseTime)
{
	m_animationTime += _elapseTime;

	if (m_animationTime >= 0.5f)
	{

		switch (m_function)
		{
			//일반 NPC
		case NPC_FUNCTION::NONE:
		{
			//대사출력
			if (m_state == NPC_STATE::INTERACT)
			{
				//대화 UI호출
				DoScript();
			}
			else
			{
				DoPattern();
			}
		}break;

		//상점NPC
		case NPC_FUNCTION::SHOP:
		{
			//상점UI 호출
		}break;

		//포켓몬센터
		case NPC_FUNCTION::HEAL:
		{
			//상호작용 중이라면, 포켓몬 치료
			if (m_state == NPC_STATE::INTERACT)
			{

			}
		}break;

		//트레이너
		case NPC_FUNCTION::TRAINER:
		{
			//트레이너 행동
			//평상시
			if (m_state == NPC_STATE::NPC_NORMAL)
			{
				//가만히 서있거나 왔다갔다
			}
			//유저 조우
			else if (m_state == NPC_STATE::ENCOUNTER)
			{
				//유저한테 달려옴
			}
			//상호작용 중
			else
			{
				//대사치고 배틀 시작
			}
		}break;

		//체육관 관장
		case NPC_FUNCTION::CHAMP:
		{}break;
		}

		m_animationTime -= 0.5f;
	}
	else if (m_animationTime >= 0.25f)
	{
		m_isMoving = false;
	}

	float value = m_animationTime / 0.5f;
	
	if (m_direction < 2)
	{
		if (m_prevPosition.y != m_position.y)
		{
			if (m_direction == DIRECTION::UP)
				m_realPosition.y = (LONG)((m_prevPosition.y - value) * MAP_TILE_SIZE);
			else
				m_realPosition.y = (LONG)((m_prevPosition.y + value) * MAP_TILE_SIZE);
		}
	}
	else
	{
		if (m_prevPosition.x != m_position.x)
		{
			if (m_direction == DIRECTION::LEFT)
				m_realPosition.x = (LONG)((m_prevPosition.x - value) * MAP_TILE_SIZE);
			else
				m_realPosition.x = (LONG)((m_prevPosition.x + value) * MAP_TILE_SIZE);
		}
	}
	
}
