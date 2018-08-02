#pragma once

#include "SingletonA.h"
#include <Windows.h>

class Time;
typedef unsigned long unlong;

class TimeManager : public MySingletonA<TimeManager>
{
	friend MySingletonA;

private:
	Time	*timer = nullptr;
	TimeManager();
	~TimeManager();

public:
	float Tick();
	unlong GetFPS();
	void SetFPS(unlong lockFPS);

	float	GetElapseTime();
	float	GetPlayTime();
	void	RenderFPS(HDC hdc, int x, int y);
};

#define TIME TimeManager::GetInst()