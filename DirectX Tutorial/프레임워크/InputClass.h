#pragma once

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