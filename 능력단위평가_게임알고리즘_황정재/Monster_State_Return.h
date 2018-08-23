#pragma once
#include "Monster_State.h"
class Monster_State_Return : public Monster_State
{
public:
	Monster_State_Return();
	~Monster_State_Return();

	void Init(Monster *_this);
	void Release();

	void Render(HDC _hdc);
	void Update(float _elapseTime = 0.0f);
};