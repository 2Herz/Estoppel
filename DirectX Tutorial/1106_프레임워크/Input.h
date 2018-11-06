#pragma once

class Input
{
private:
	bool m_Keys[256] = {};

public:
	Input();
	Input(const Input&);
	~Input();

public:
	void Initialize();
	
	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);
};