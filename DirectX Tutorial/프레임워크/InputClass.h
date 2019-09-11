#pragma once

/*
	이 곳은 입력(Input) 클래스이다.

	이 클래스는 이 DIrectX 11 프로그램에서의 기본 입력을 관리하는 클래스이다.
*/

const unsigned int MAX_KEYS = 256;

class InputClass
{
public:
	void Init();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool m_keys[MAX_KEYS];

public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();
};