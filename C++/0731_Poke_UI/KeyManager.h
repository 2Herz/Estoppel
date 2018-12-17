#pragma once

#include <Windows.h>

class KeyManager
{
private:
	KeyManager() = default;

public:
	static KeyManager& GetInstance()
	{
		static KeyManager instance;

		return instance;
	}

//////////////// base ////////////////

public:
	bool	m_isFocus		= true;
	bool	m_isDown[256]	= {};
	bool	m_isUp[256]		= {};
	bool	m_isToggle[256]	= {};


public:
	void	SetFocus(bool _focus);
	bool	OnceKeyDown(int _key);
	bool	OnceKeyUp(int _key);
	bool	StayKeyDown(int _key);
	bool	IsToggleKey(int _key);

};

#define KEYMGR	KeyManager::GetInstance()