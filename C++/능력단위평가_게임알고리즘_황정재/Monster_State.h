#pragma once

#include "FPOINT.h"
#include <Windows.h>

enum MONSTER_STATE
{
	MS_IDLE,
	MS_PROWL,
	MS_CHASE,
	MS_RETURN
};

class Monster;

class Monster_State
{
protected:
	Monster * m_this = nullptr;
	MONSTER_STATE m_state;

public:
	virtual ~Monster_State() = default;

	virtual void Init(Monster *_this) = 0;
	virtual void Release() = 0;

	virtual void Render(HDC _hdc) = 0;
	virtual void Update(float _elapseTime = 0.0f) = 0;

	inline MONSTER_STATE	GetState()
	{
		return m_state;
	}
};
