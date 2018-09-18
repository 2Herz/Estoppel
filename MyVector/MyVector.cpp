#include "MyVector.h"

MyVector::MyVector()
{
	x = 0;
	y = 0;
	z = 0;
}

MyVector::MyVector(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

//	기본연산
MyVector MyVector::operator+(const MyVector& right)
{
	return MyVector(x + right.x, y + right.y, z + right.z);
}
MyVector MyVector::operator-(const MyVector& right)
{
	return MyVector(x - right.x, y - right.y, z - right.z);
}
MyVector MyVector::operator*(const MyVector& right)
{
	return MyVector(x * right.x, y * right.y, z * right.z);
}
MyVector MyVector::operator/(const MyVector& right)
{
	return MyVector(x / right.x, y / right.y, z / right.z);
}

//	복합연산자
MyVector MyVector::operator+=(const MyVector& right)
{
	return MyVector(x += right.x, y += right.y, z += right.z);
}
MyVector MyVector::operator-=(const MyVector& right)
{
	return MyVector(x -= right.x, y -= right.y, z -= right.z);
}
MyVector MyVector::operator*=(const MyVector& right)
{
	return MyVector(x *= right.x, y *= right.y, z *= right.z);
}
MyVector MyVector::operator/=(const MyVector& right)
{
	return MyVector(x /= right.x, y /= right.y, z /= right.z);
}

float MyVector::Length(MyVector &right)
{
	return sqrtf(powf(right.x, 2) + powf(right.y, 2) + powf(right.z, 2));
}

/*MyVector MyVector::Scailing(MyVector &right, float scalar)
{
	return MyVector(right.x * scalar, right.y * scalar, right.z * scalar);
}*/

MyVector MyVector::Normal(MyVector &right)
{
	float len = Length(right);

	return MyVector(right.x / len, right.y / len, right.z / len);
}

float MyVector::Dot(MyVector &right)
{
	return x * right.x + y * right.y + z * right.z;
}

MyVector MyVector::Cross(MyVector &right)
{
	return MyVector(y * right.z - z * right.y, z * right.x - x * right.z, x * right.y - y - right.x);
}

//	벡터 * 스칼라 연산을 위한 연산자
MyVector MyVector::operator*(float scalar)
{
	return MyVector(x * scalar, y * scalar, z * scalar);
}

MyVector MyVector::operator*=(float scalar)
{
	return MyVector(x *= scalar, y *= scalar, z *= scalar);
}

MyVector MyVector::operator/(float scalar)
{
	return MyVector(x / scalar, y / scalar, z / scalar);
}

MyVector MyVector::operator/=(float scalar)
{
	return MyVector(x /= scalar, y /= scalar, z /= scalar);
}

//	교환법칙
MyVector operator*(float scalar, MyVector& right)
{
	return MyVector(scalar * right.x, scalar * right.y, scalar * right.z);
}
MyVector operator*=(float scalar, MyVector & right)
{
	return MyVector(scalar *= right.x, scalar *= right.y, scalar * right.z);
}
MyVector operator/(float scalar, MyVector & right)
{
	return MyVector(scalar / right.x, scalar / right.y, scalar / right.z);
}
MyVector operator/=(float scalar, MyVector & right)
{
	return MyVector(scalar /= right.x, scalar /= right.y, scalar /= right.z);
}