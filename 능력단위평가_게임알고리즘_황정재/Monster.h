#pragma once
#include "FPOINT.h"
#include "Monster_State.h"

class Monster
{
	FPOINT m_Pos;			//	�÷��̾� ��ġ
	FPOINT m_TargetPos;			//	Ÿ��
	float m_Speed;				//	�̵��ӵ�

	Monster_State *m_pState;	//	����
	MONSTER_STATE m_State;

private:
	void TransState();

public:
	Monster();
	~Monster();

	void Render(HDC _hdc);
	void Update(float _elapseTime = 0.0f);

	void SetSpeed(float _speed)
	{
		m_Speed = _speed;
	}
	float GetSpeed()
	{
		return m_Speed;
	}
	FPOINT GetPos()
	{
		return m_Pos;
	}
	void SetPos(FPOINT _pos)
	{
		m_Pos = _pos;
	}
	void AddPos(FPOINT _add)
	{
		m_Pos = m_Pos + _add * m_Speed;
	}
	FPOINT SetMonsterPos(FPOINT _pos)
	{
		m_Pos = _pos;
	}
	FPOINT GetTargetPos()
	{
		return m_TargetPos;
	}
	void SetState(MONSTER_STATE _new)
	{
		m_State = _new;
	}
	void SetTarget(FPOINT _target)
	{
		m_TargetPos = _target;
		m_State = MONSTER_STATE::MS_CHASE;
	}
};