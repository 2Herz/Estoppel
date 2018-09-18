#pragma once
#include <iostream>
#include <DirectXMath.h>
using namespace DirectX;
using namespace std;

class MyVector
{
public:
	float x;
	float y;
	float z;

public:
	MyVector();
	MyVector(float _x, float _y, float _z);
	~MyVector() = default;

	//	기본연산자 +, -, *, /
	MyVector  operator+(const MyVector& right);
	MyVector  operator-(const MyVector& right);
	MyVector  operator*(const MyVector& right);
	MyVector  operator/(const MyVector& right);

	//	복합대입연산자 +=, -=, *=, /=
	MyVector operator+=(const MyVector& right);
	MyVector operator-=(const MyVector& right);
	MyVector operator*=(const MyVector& right);
	MyVector operator/=(const MyVector& right);

	//	벡터의 스칼라의 연산을 위한 연산자 오버로딩
	MyVector operator*(float scalar);
	MyVector operator*=(float scalar);
	MyVector operator/(float scalar);
	MyVector operator/=(float scalar);

	//	벡터의 길이를 구하는 함수
	float Length(MyVector &right);
	//	벡터의 크기를 조절하는 함수
	//MyVector Scailing(MyVector &right, float scalar);
	//	단위벡터를 구하는 함수
	MyVector Normal(MyVector &right);
	//	벡터의 내적을 구하는 함수
	float Dot(MyVector &right);
	//	벡터의 외적을 구하는 함수
	MyVector Cross(MyVector &right);
};

//	교환법칙
MyVector operator*(float scalar, MyVector& right);
MyVector operator*=(float scalar, MyVector& right);
MyVector operator/(float scalar, MyVector& right);
MyVector operator/=(float scalar, MyVector& right);