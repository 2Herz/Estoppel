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

	//	현재 위치를 중점으로 하는 사각형
	RECT	GetRect(int _size);

	//	거리 구하기( 벡터 길이 )
	float	Dist();
	FPOINT	Nomal();
};