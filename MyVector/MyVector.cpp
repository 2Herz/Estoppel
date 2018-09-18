#include "MyVector.h"

//	기본연산
MyVector MyVector::operator+(const MyVector& right)
{
	MyVector result = 
	{
		x + right.x,
		y + right.y,
		z + right.z
	};

	return result;
}
MyVector MyVector::operator-(const MyVector& right)
{
	MyVector result = 
	{
		x - right.x,
		y - right.y,
		z - right.z
	};

	return result;
}
MyVector MyVector::operator*(const MyVector& right)
{
	MyVector result = 
	{
		x * right.x,
		y * right.y,
		z * right.z,
	};

	return result;
}
MyVector MyVector::operator/(const MyVector& right)
{
	MyVector result = 
	{
		x / right.x,
		y / right.y,
		z / right.z
	};

	return result;
}

//	복합연산자
MyVector MyVector::operator+=(const MyVector& right)
{
	MyVector result = 
	{
		x += right.x,
		y += right.y,
		z += right.z
	};

	return result;
}
MyVector MyVector::operator-=(const MyVector& right)
{
	MyVector result = 
	{
		x -= right.x,
		y -= right.y,
		z -= right.z
	};

	return result;
}
MyVector MyVector::operator*=(const MyVector& right)
{
	MyVector result = 
	{
		x *= right.x,
		y *= right.y,
		z *= right.z
	};

	return result;
}
MyVector MyVector::operator/=(const MyVector& right)
{
	MyVector result = 
	{
		x /= right.x,
		y /= right.y,
		z /= right.z
	};

	return result;
}

//	스칼라 연산
MyVector operator*(MyVector & right, float scala)
{
	MyVector result =
	{
		right.x * scala,
		right.y * scala,
		right.z * scala
	};

	return result;
}
MyVector operator*=(MyVector & right, float scala)
{
	MyVector result =
	{
		right.x *= scala,
		right.y *= scala,
		right.z *= scala
	};
	return result;
}
MyVector operator/(MyVector & right, float scala)
{
	MyVector result =
	{
		right.x / scala,
		right.y / scala,
		right.z / scala
	};
	return result;
}
MyVector operator/=(MyVector & right, float scala)
{
	MyVector result =
	{
		right.x /= scala,
		right.y /= scala,
		right.z /= scala
	};
	return result;
}
//	교환법칙
MyVector operator*(float scala, MyVector& right)
{
	MyVector result =
	{
		scala * right.x,
		scala * right.y,
		scala * right.z
	};

	return result;
}
MyVector operator*=(float scala, MyVector & right)
{
	MyVector result =
	{
		scala *= right.x,
		scala *= right.y,
		scala *= right.z
	};

	return result;
}
MyVector operator/(float scala, MyVector & right)
{
	MyVector result =
	{
		scala / right.x,
		scala / right.y,
		scala / right.z
	};

	return result;
}
MyVector operator/=(float scala, MyVector & right)
{
	MyVector result =
	{
		scala /= right.x,
		scala /= right.y,
		scala /= right.z
	};

	return result;
}