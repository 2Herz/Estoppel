#pragma once

class TimeClass
{
	bool			m_isHighTimer = false;
	float			m_timeResolusion = 0.0f;
	float			m_timeElapsed = 0.0f;
	__int64			m_lastTime = 0;
	__int64			m_nowTime = 0;

	unsigned long	m_FPS = 0;
	unsigned long	m_FPSCount = 0;
	float			m_FPSTimeElapsed = 0.0f;

	unsigned long	m_lockFPS = 60;
	float			m_lockTime = 1.0f / m_lockFPS;

	float			m_playTime = 0.0f;

private:
	void	Initialize();
	void	Release();

public:
	TimeClass();
	~TimeClass();

	float Tick();


	unsigned long	GetFPS()
	{
		return m_FPS;
	}

	void	SetFPS(unsigned long _lockFPS)
	{
		if (_lockFPS == 0 || _lockFPS == m_lockFPS)
			return;

		m_lockFPS = _lockFPS;
		m_lockTime = 1.0f / m_lockFPS;
	}

	float			GetElapsedTime()
	{
		return m_timeElapsed;
	}

	float			GetPlayTime()
	{
		return m_playTime;
	}
};