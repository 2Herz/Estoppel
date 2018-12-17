#pragma once

#include <Windows.h>

class FPOINT
{
public:
	float x, y;

public:
	FPOINT(float _x = 0.0f, float _y = 0.0f);
	FPOINT(int _x, int _y);

	operator POINT();
	FPOINT operator-(FPOINT _right);
	FPOINT operator+(FPOINT _right);
	FPOINT operator*(float _scala);

	//	���� ��ġ�� �������� �ϴ� �簢��
	RECT	GetRect(int _size);

	//	�Ÿ� ���ϱ�( ���� ���� )
	float	Dist();
	FPOINT	Nomal();
};