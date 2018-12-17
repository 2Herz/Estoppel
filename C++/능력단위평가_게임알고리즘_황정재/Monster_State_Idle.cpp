#include "stdafx.h"
#include "Monster_State_Idle.h"

Monster_State_Idle::Monster_State_Idle()
{
}

Monster_State_Idle::~Monster_State_Idle()
{
}

void Monster_State_Idle::Init(Monster * _this)
{
	m_this = _this;
	m_state = MONSTER_STATE::MS_IDLE;
}

void Monster_State_Idle::Release()
{
}

void Monster_State_Idle::Render(HDC _hdc)
{
	FPOINT Monster = m_this->GetPos();

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hOldBrush = SelectBrush(_hdc, hBrush);

	RECT monster = Monster.GetRect(100);
	Ellipse(_hdc, monster.left, monster.top, monster.right, monster.bottom);

	DeleteObject(SelectBrush(_hdc, hOldBrush));
}

void Monster_State_Idle::Update(float _elapseTime)
{
	FPOINT pos = m_this->GetPos();

	m_changeTime -= _elapseTime;

	if (m_changeTime < 0)
	{
		m_this->SetState(MONSTER_STATE::MS_PROWL);
	}

	if ((g_PlayerPos - pos).Dist() < 100)
	{
		m_this->SetState(MONSTER_STATE::MS_CHASE);
	}
}