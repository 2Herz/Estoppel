#include "MyVector.h"

int main()
{
	MyVector v1(1, 2, 3);
	MyVector v2(-5, -3, -8);

	cout << "v1 x, y, z : " << "(" << v1.x << "," << v1.y << "," << v1.z << ")" << endl;
	cout << "v2 x, y, z : " << "(" << v2.x << "," << v2.y << "," << v2.z << ")" << endl;

	//	+,-,*,/
	MyVector v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;

	cout << endl;
	cout << "º¤ÅÍÀÇ ¿¬»ê" << endl;
	cout << "(" << v3.x << "," << v3.y << "," << v3.z << ")" << endl;

	cout << endl;
	cout << "º¤ÅÍÀÇ ³»Àû" << endl;
	cout << "(" << v1.Dot(v2) << ")" << endl;
	
	cout << endl;
	cout << "º¤ÅÍÀÇ ¿ÜÀû" << endl;
	MyVector v4 = v1.Cross(v2);
	cout << "(" << v4.x << "," << v4.y << "," << v4.z << ")" << endl;

	cout << endl;
	cout << "´ÜÀ§º¤ÅÍ ¸¸µé±â" << endl;
	MyVector v5;
	v5.Normal(v4);
	cout << "(" << v5.x << "," << v5.y << "," << v5.z << ")" << endl;
	
	cout << endl;
	cout << "º¤ÅÍÀÇ ±æÀÌ" << endl;
	cout << v1.Length(v1) << endl;
	cout << v2.Length(v1) << endl;
	cout << v3.Length(v1) << endl;
	cout << v4.Length(v1) << endl;
	cout << v5.Length(v1) << endl;

	cout << endl;

	//	º¤ÅÍ¿Í ½ºÄ®¶ó ¿¬»ê
	float scalar = 5.0f;

	v1 = (v2 * v3) * scalar;

	cout << v1.x << endl;
	cout << v1.y << endl;
	cout << v1.z << endl;

	cout << endl;
	v2 = scalar * v1;

	cout << v2.x << endl;
	cout << v2.y << endl;
	cout << v2.z << endl;

	return 0;
}