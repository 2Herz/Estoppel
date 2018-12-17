#include "TimeClass.h"
#include "Global.h"

TimeClass::TimeClass()
{
	Initialize();
}
TimeClass::~TimeClass()
{
	Release();
}

void TimeClass::Initialize()
{
	LARGE_INTEGER	periodRrequency = {};
	m_isHighTimer = QueryPerformanceFrequency(&periodRrequency);

	if (m_isHighTimer == true)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_lastTime);
		m_timeResolusion = 1.0f / periodRrequency.QuadPart;
	}
	else
	{
		timeBeginPeriod(1);

		m_lastTime = timeGetTime();
		m_timeResolusion = 0.001f;
	}
}

void TimeClass::Release()
{
	timeEndPeriod(1);
}

float TimeClass::Tick()
{
	do
	{
		if (m_isHighTimer)
			QueryPerformanceCounter((LARGE_INTEGER*)&m_nowTime);
		else
			m_nowTime = timeGetTime();

		m_timeElapsed = (m_nowTime - m_lastTime) * m_timeResolusion;

	} while (m_timeElapsed <= m_lockTime);

	m_lastTime = m_nowTime;

	m_FPSCount++;

	m_FPSTimeElapsed += m_timeElapsed;

	m_playTime += m_timeElapsed;

	if (m_FPSTimeElapsed > 1.0f)
	{
		m_FPS = m_FPSCount;
		m_FPSCount = 0;
		m_FPSTimeElapsed -= 1.0f;
	}

	return m_timeElapsed;
}