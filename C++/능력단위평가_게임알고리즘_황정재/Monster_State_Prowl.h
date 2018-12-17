#pragma once
#include "Monster_State.h"
class Monster_State_Prowl : public Monster_State
{
private:
	float m_changeTime = 2;
	int m_rect = 0;
public:
	Monster_State_Prowl();
	~Monster_State_Prowl();

	void Init(Monster *_this);
	void Release();

	void Render(HDC _hdc);
	void Update(float _elapseTime = 0.0f);
};