#pragma once
#include "Monster_State.h"
class Monster_State_Idle : public Monster_State
{
private:
	float m_changeTime = 2;
public:
	Monster_State_Idle();
	~Monster_State_Idle();

	void Init(Monster *_this);
	void Release();

	void Render(HDC _hdc);
	void Update(float _elapseTime = 0.0f);
};