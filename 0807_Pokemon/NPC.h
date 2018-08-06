#pragma once
#include "ImgClass.h"

/*
NPC 행동
1. 일반 NPC
한 방향 주시하다가 말걸면 캐릭터를 쳐다보며 스크립트 재생
*/

//NPC 기능
enum NPC_FUNCTION 
{
	NONE,		//일반
	HEAL,		//포켓몬센터
	SHOP,		//상점
	TRAINER,	//일반 트레이너
	CHAMP,		//체육관 관장
};

//NPC 상태
enum NPC_STATE
{
	NPC_NORMAL,		//일반
	ENCOUNTER,	//조우
	COMING,	
	INTERACT,	//상호작용
	FINISHED,
};

//NPC 행동패턴
enum NPC_PATTERN
{
	STARRING, //주시
	TURN_ARROUND_CLOCKWISE, //주변 시계방향 빙글빙글 배회
	TURN_ARROUND_COUNTER_CLOCKWISE, //반시계방향 배회
	TURNING, //제자리 빙글빙글
	RANDOM, //랜덤 행동
};

class NPC
{
private:
	int m_number;			//NPC 번호
	int m_function;			//기능
	int m_searchDistance;	//탐색거리
	int m_state;			//상태
	int m_mapNumber;
	
	POINT m_prevPosition;
	POINT m_position;		//NPC 위치 타일 좌표
	POINT m_rootPosition;	//NPC 원 위치 좌표
	POINT m_realPosition;   //NPC 실제 위치 좌표
	int m_direction;
	int m_step;
	bool m_isMoving = false;
	int m_pattern;			//NPC 패턴
	SIZE m_moveBox;			//NPC 행동 박스크기
	POINT m_moveBoxPosition; //행동박스 좌표
	float m_animationTime;		//NPC 애니메이션 시간

	int m_x_max; //맵 width
	int m_y_max; //맵 height

private:
	void GoLeft();
	void GoRight();
	void GoUp();
	void GoDown();
	void TurnUp();
	void TurnDown();
	void TurnLeft();
	void TurnRight();
	void DoPattern();
	void DoScript();
	bool CheckPlayer();

public:
	NPC();
	NPC(int _number,int _mapNumber, int _function, int _direction, int _pattern, int _searchDistance, POINT _position, SIZE _moveBoxSize);
	~NPC();

	int GetState()
	{
		return m_state;
	}
	void SetState(int _state)
	{
		m_state = _state;
	}

	POINT GetRealPosition()
	{
		return m_realPosition;
	}

	POINT GetRootPosition()
	{
		return m_rootPosition;
	}

	POINT GetPosition()
	{
		return m_position;
	}

	SIZE GetMoveBox()
	{
		return m_moveBox;
	}

	void SetPosition(POINT _position)
	{
		m_position = _position;
	}

	int GetNumber()
	{
		return m_number;
	}

	int GetDirection()
	{
		return m_direction;
	}

	int GetStep()
	{
		return m_step;
	}

	bool IsMoving()
	{
		return m_isMoving;
	}

	void DoAction(float _elapseTime);
};

