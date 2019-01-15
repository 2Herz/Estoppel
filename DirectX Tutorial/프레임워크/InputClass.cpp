#include "InputClass.h"

InputClass::InputClass()
{
}

InputClass::InputClass(const InputClass& other)
{
}

InputClass::~InputClass()
{
}


void InputClass::Init()
{
	//	초기화
	for (int index = 0; index < MAX_KEYS; index++)
	{
		m_keys[index] = false;
	}

	return;
}

void InputClass::KeyDown(unsigned int input)
{
	//	키가 눌렸을 시 해당 상태를 배열에 저장
	m_keys[input] = true;
	return;
}

void InputClass::KeyUp(unsigned int input)
{
	//	키가 해제될 시 해당 상태를 배열에 저장
	m_keys[input] = true;
	return;
}

bool InputClass::IsKeyDown(unsigned int key)
{
	//	키의 상태를 반환(누름/누르지 않음)
	return m_keys[key];
}