#include "KeyManager.h"

void KeyManager::SetFocus(bool _focus)
{
	m_isFocus = _focus;
}

bool KeyManager::OnceKeyDown(int _key)
{
	if (m_isFocus && GetAsyncKeyState(_key) & 0x8000)
	{
		if (m_isDown[_key] == false)
		{
			m_isDown[_key] = true;
			return true;
		}
	}
	else
	{
		m_isDown[_key] = false;
	}
	return false;
}

bool KeyManager::OnceKeyUp(int _key)
{
	if (m_isFocus && GetAsyncKeyState(_key) & 0x8000)
	{
		m_isUp[_key] = true;
	}
	else
	{
		if (m_isUp[_key] == true)
		{
			m_isUp[_key] = false;
			return true;
		}
	}
	return false;
}

bool KeyManager::StayKeyDown(int _key)
{
	return (m_isFocus && GetAsyncKeyState(_key) & 0x8000);
}

bool KeyManager::IsToggleKey(int _key)
{
	if (OnceKeyUp(_key))
	{
		m_isToggle[_key] = !m_isToggle[_key];
	}
	return m_isToggle[_key];
}
