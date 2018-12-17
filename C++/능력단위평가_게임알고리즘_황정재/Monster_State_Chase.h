#pragma once
#include "Monster_State.h"
class Monster_State_Chase : public Monster_State
{
public:
	Monster_State_Chase();
	~Monster_State_Chase();

	void Init(Monster *_this);
	void Release();

	void Render(HDC _hdc);
	void Update(float _elapseTime = 0.0f);
};