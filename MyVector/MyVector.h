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
	//	������ �� �Ҹ���
	MyVector();
	MyVector(float _x, float _y, float _z);
	~MyVector() = default;

	//	�⺻������ +, -, *, /
	MyVector  operator+(const MyVector& right);
	MyVector  operator-(const MyVector& right);
	MyVector  operator*(const MyVector& right);
	MyVector  operator/(const MyVector& right);

	//	���մ��Կ����� +=, -=, *=, /=
	MyVector operator+=(const MyVector& right);
	MyVector operator-=(const MyVector& right);
	MyVector operator*=(const MyVector& right);
	MyVector operator/=(const MyVector& right);

	//	������ ��Į���� ������ ���� ������ �����ε�
	MyVector operator*(float scalar);
	MyVector operator*=(float scalar);
	MyVector operator/(float scalar);
	MyVector operator/=(float scalar);

	//	������ ���̸� ���ϴ� �Լ�
	float Length(MyVector &right);
	//	�������͸� ���ϴ� �Լ�
	MyVector Normal(MyVector &right);
	//	������ ������ ���ϴ� �Լ�
	float Dot(MyVector &right);
	//	������ ������ ���ϴ� �Լ�
	MyVector Cross(MyVector &right);
};

//	��ȯ��Ģ
MyVector operator*(float scalar, MyVector& right);
MyVector operator*=(float scalar, MyVector& right);
MyVector operator/(float scalar, MyVector& right);
MyVector operator/=(float scalar, MyVector& right);