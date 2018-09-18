#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class MyVector
{
public:
	float x;
	float y;
	float z;
	float scala;

public:
	MyVector  operator+(const MyVector& right);
	MyVector  operator-(const MyVector& right);
	MyVector  operator*(const MyVector& right);
	MyVector  operator/(const MyVector& right);

	MyVector operator+=(const MyVector& right);
	MyVector operator-=(const MyVector& right);
	MyVector operator*=(const MyVector& right);
	MyVector operator/=(const MyVector& right);

	MyVector operator*(const MyVector& right);
	MyVector operator*=(const MyVector& right);
	MyVector operator/(const MyVector& right);
	MyVector operator/=(const MyVector& right);

private:
	MyVector Length();
	MyVector Scailing();
	MyVector Normal();
	MyVector Cross();
};

MyVector operator*(MyVector& right, float scala);
MyVector operator*=(MyVector& right, float scala);
MyVector operator/(MyVector& right, float scala);
MyVector operator/=(MyVector& right, float scala);
MyVector operator*(float scala, MyVector& right);
MyVector operator*=(float scala, MyVector& right);
MyVector operator/(float scala, MyVector& right);
MyVector operator/=(float scala, MyVector& right);