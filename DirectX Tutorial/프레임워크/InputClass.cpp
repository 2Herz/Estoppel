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
	//	�ʱ�ȭ
	for (int index = 0; index < MAX_KEYS; index++)
	{
		m_keys[index] = false;
	}

	return;
}

void InputClass::KeyDown(unsigned int input)
{
	//	Ű�� ������ �� �ش� ���¸� �迭�� ����
	m_keys[input] = true;
	return;
}

void InputClass::KeyUp(unsigned int input)
{
	//	Ű�� ������ �� �ش� ���¸� �迭�� ����
	m_keys[input] = true;
	return;
}

bool InputClass::IsKeyDown(unsigned int key)
{
	//	Ű�� ���¸� ��ȯ(����/������ ����)
	return m_keys[key];
}