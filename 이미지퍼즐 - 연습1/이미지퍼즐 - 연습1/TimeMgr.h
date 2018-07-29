#pragma once

#include "Global.h"
#include "SingletonA.h"

class TimeClass;

class TimeMgr : public SingletonA<TimeMgr>
{
	friend SingletonA;
private:
	TimeClass * m_timer = nullptr;

private:
	TimeMgr();
	~TimeMgr();

public:
	float Tick();

	unsigned long	GetFPS();
	void			SetFPS(unsigned long _lockFPS);

	float			GetElapsedTime();

	float			GetPlayTime();

	void			Render(HDC _hdc, int _x, int _y);
};

#define TIME TimeMgr::GetInstance()