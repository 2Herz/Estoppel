#include "stdafx.h"
#include "Input.h"

Input::Input()
{
}

Input::Input(const Input& other)
{
}

Input::~Input()
{
}

void Input::Initialize()
{
	//	키 배열 초기화
	for (int i = 0; i < 256; ++i)
	{
		m_Keys[i] = false;
	}
}

void Input::KeyDown(unsigned int input)
{
	//	키가 눌리면 해당 키값을 true
	m_Keys[input] = true;
}

void Input::KeyUp(unsigned int input)
{
	//	키가 떼졌으면 해당 키값을 false
	m_Keys[input] = false;
}

bool Input::IsKeyDown(unsigned int key)
{
	//	현재 키값의 상태를 반환
	return m_Keys[key];
}