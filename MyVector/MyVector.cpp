#include "MyVector.h"

//	�⺻����
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

//	���տ�����
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

//	��Į�� ����
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
//	��ȯ��Ģ
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