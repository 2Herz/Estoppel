#include "stdafx.h"
#include "InputClass.h"

InputClass::InputClass()
{
}

InputClass::InputClass(const InputClass &)
{
}

InputClass::~InputClass()
{
}

void InputClass::Initialize()
{
	//	키 배열을 초기화합니다.
	for (int i = 0; i < 256; i++)
	{
		m_Keys[i] = false;
	}
}

void InputClass::KeyDown(unsigned int input)
{
	//	키가 눌렸다면 해당 키 값을 true로 저장합니다.
	m_Keys[input] = true;
}

void InputClass::KeyUp(unsigned int input)
{
	//	키가 해제되었다면 해당 키 값을 false로 저장합니다.
	m_Keys[input] = false;
}

bool InputClass::IsKeyDown(unsigned int key)
{
	//	현재 키 값이 눌러졌는지 아닌지 상태를 반환합니다.
	return m_Keys[key];
}
