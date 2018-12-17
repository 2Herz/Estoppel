#include "stdafx.h"
#include "FPOINT.h"
#include <cmath>

FPOINT::FPOINT(float _x, float _y)
{
	x = _x;
	y = _y;
}
FPOINT::FPOINT(int _x, int _y)
{
	x = float(_x);
	y = float(_y);
}
FPOINT::operator POINT()
{
	POINT	result = { LONG(x), LONG(y) };
	return result;
}
FPOINT FPOINT::operator-(FPOINT _right)
{
	return FPOINT(x - _right.x, y - _right.y);
}
FPOINT FPOINT::operator+(FPOINT _right)
{
	return FPOINT(x + _right.x, y + _right.y);
}
FPOINT FPOINT::operator*(float _scala)
{
	return FPOINT(x * _scala, y * _scala);
}
RECT	FPOINT::GetRect(int _size)
{
	RECT rt = { 0, 0, _size, _size };
	OffsetRect(&rt, int(x - _size / 2), int(y - _size / 2));

	return rt;
}
float	FPOINT::Dist()
{
	return sqrtf(powf(x, 2) + powf(y, 2));
}

FPOINT FPOINT::Nomal()
{
	float dist = sqrtf(powf(x, 2) + powf(y, 2));

	return FPOINT(x / dist, y / dist);
}