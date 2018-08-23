#include "stdafx.h"
#include "Monster.h"

#include "Monster_State_Idle.h"
#include "Monster_State_Prowl.h"
#include "Monster_State_Chase.h"
#include "Monster_State_Return.h"

void Monster::TransState()
{
	if (m_pState != nullptr)
	{
		m_pState->Release();
		delete m_pState;
	}

	switch (m_State)
	{
	case MONSTER_STATE::MS_IDLE:
		m_pState = new Monster_State_Idle;
		break;
	case MONSTER_STATE::MS_PROWL:
		m_pState = new Monster_State_Prowl;
		break;
	case MONSTER_STATE::MS_CHASE:
		m_pState = new Monster_State_Chase;
		break;
	case MONSTER_STATE::MS_RETURN:
		m_pState = new Monster_State_Return;
		break;
	}

	m_pState->Init(this);
}

Monster::Monster()
{
	m_Pos = FPOINT(400, 400);
	m_State = MONSTER_STATE::MS_IDLE;
	m_Speed = 50;

	TransState();
}

Monster::~Monster()
{
}

void Monster::Render(HDC _hdc)
{
	if (m_pState != nullptr)
	{
		m_pState->Render(_hdc);
	}
}

void Monster::Update(float _elapseTime)
{
	if (m_pState != nullptr)
	{
		if (m_State != m_pState->GetState())
		{
			TransState();
		}
		m_pState->Update(_elapseTime);
	}
}
