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
	//	Ű �迭 �ʱ�ȭ
	for (int i = 0; i < 256; ++i)
	{
		m_Keys[i] = false;
	}
}

void Input::KeyDown(unsigned int input)
{
	//	Ű�� ������ �ش� Ű���� true
	m_Keys[input] = true;
}

void Input::KeyUp(unsigned int input)
{
	//	Ű�� �������� �ش� Ű���� false
	m_Keys[input] = false;
}

bool Input::IsKeyDown(unsigned int key)
{
	//	���� Ű���� ���¸� ��ȯ
	return m_Keys[key];
}