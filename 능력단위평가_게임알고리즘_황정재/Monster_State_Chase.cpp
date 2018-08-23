#include "stdafx.h"
#include "Monster_State_Chase.h"

Monster_State_Chase::Monster_State_Chase()
{
}

Monster_State_Chase::~Monster_State_Chase()
{
}

void Monster_State_Chase::Init(Monster * _this)
{
	m_this = _this;
	m_state = MONSTER_STATE::MS_CHASE;
	m_this->SetSpeed(50);
}

void Monster_State_Chase::Release()
{
}

void Monster_State_Chase::Render(HDC _hdc)
{
	FPOINT	pos = m_this->GetPos();

	HBRUSH	hBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH	hOldBrush = SelectBrush(_hdc, hBrush);

	RECT rt = pos.GetRect(100);
	Ellipse(_hdc, rt.left, rt.top, rt.right, rt.bottom);

	DeleteObject(SelectBrush(_hdc, hOldBrush));
}

void Monster_State_Chase::Update(float _elapseTime)
{
	FPOINT	pos = m_this->GetPos();
	FPOINT	vec = g_PlayerPos - pos;

	if (vec.Dist() > 200)
	{
		m_this->SetState(MONSTER_STATE::MS_RETURN);
	}
	else if (vec.Dist() > 5)
	{
		FPOINT	dir = vec.Nomal();
		m_this->AddPos(dir * _elapseTime);
	}
}