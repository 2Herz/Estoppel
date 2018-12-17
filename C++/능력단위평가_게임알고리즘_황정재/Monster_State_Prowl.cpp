#include "stdafx.h"
#include "Monster_State_Prowl.h"

Monster_State_Prowl::Monster_State_Prowl()
{
}

Monster_State_Prowl::~Monster_State_Prowl()
{
}

void Monster_State_Prowl::Init(Monster * _this)
{
	srand(GetTickCount());
	m_this = _this;
	m_state = MONSTER_STATE::MS_PROWL;
	m_this->SetSpeed(20);
	m_rect = rand() % 4;
}

void Monster_State_Prowl::Release()
{
}

void Monster_State_Prowl::Render(HDC _hdc)
{
	FPOINT Monster = m_this->GetPos();

	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hOldBrush = SelectBrush(_hdc, hBrush);

	RECT monster = Monster.GetRect(100);
	Ellipse(_hdc, monster.left, monster.top, monster.right, monster.bottom);

	DeleteObject(SelectBrush(_hdc, hOldBrush));
}

void Monster_State_Prowl::Update(float _elapseTime)
{
	FPOINT pos = m_this->GetPos();

	switch (m_rect)
	{
	case 0:
		pos.x -= m_this->GetSpeed() * _elapseTime;
		break;
	case 1:
		pos.y -= m_this->GetSpeed() * _elapseTime;
		break;
	case 2:
		pos.x += m_this->GetSpeed() * _elapseTime;
		break;
	case 3:
		pos.y += m_this->GetSpeed() * _elapseTime;
		break;
	}
	if (pos.x < 200)		pos.x = 200;
	else if (pos.x > 600)	pos.x = 600;
	if (pos.y < 200)		pos.y = 200;
	else if (pos.y > 600)	pos.y = 600;
	m_this->SetPos(pos);

	m_changeTime -= _elapseTime;

	if (m_changeTime < 0)
	{
		m_state = MONSTER_STATE::MS_IDLE;
		m_changeTime = float(rand() % 2);
	}

	if ((g_PlayerPos - pos).Dist() < 100)
	{
		m_this->SetState(MONSTER_STATE::MS_CHASE);
	}
}