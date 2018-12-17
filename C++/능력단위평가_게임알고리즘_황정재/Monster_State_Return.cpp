#include "stdafx.h"
#include "Monster_State_Return.h"

Monster_State_Return::Monster_State_Return()
{
}

Monster_State_Return::~Monster_State_Return()
{
}

void Monster_State_Return::Init(Monster * _this)
{
	m_this = _this;
	m_state = MONSTER_STATE::MS_RETURN;
	m_this->SetSpeed(200);
}

void Monster_State_Return::Release()
{
}

void Monster_State_Return::Render(HDC _hdc)
{
	FPOINT Monster = m_this->GetPos();

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOldBrush = SelectBrush(_hdc, hBrush);

	RECT monster = Monster.GetRect(100);
	Ellipse(_hdc, monster.left, monster.top, monster.right, monster.bottom);

	DeleteObject(SelectBrush(_hdc, hOldBrush));
}

void Monster_State_Return::Update(float _elapseTime)
{
	FPOINT	pos = m_this->GetPos();
	FPOINT	targetPos = { 400, 400 };
	FPOINT	vec = targetPos - pos;

	if (vec.Dist() < 5)
	{
		m_this->SetState(MONSTER_STATE::MS_IDLE);
	}
	else
	{
		if (pos.x > 400)		pos.x -= m_this->GetSpeed() * _elapseTime;
		else if (pos.x < 400)	pos.x += m_this->GetSpeed() * _elapseTime;
		if (pos.y > 400)		pos.y -= m_this->GetSpeed() * _elapseTime;
		else if (pos.y < 400)	pos.y += m_this->GetSpeed() * _elapseTime;
		m_this->SetPos(pos);
	}
}