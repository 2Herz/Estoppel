#include <iostream>
#include "TemplateDLL.h"
using namespace std;

int main()
{
	TemplateDLL<int> listInt;
	TemplateDLL<float> listFloat;

	for (int i = 0; i < 100; i++)
	{
		listInt.push_back(i + 1);
	}

	TemplateDLL<int>::iterator iter;

	for (iter = listInt.begin(); iter != listInt.end(); ++iter)
	{
		cout << " £ü " << *iter << " £ü " << endl;
	}

	cout << "============================================================" << endl;

	for (float i = 0; i < 100; i++)
	{
		listFloat.push_back(i + 1);
	}

	TemplateDLL<float>::Reverse_iterator iter2;

	for (iter2 = listFloat.rbegin(); iter2 != listFloat.rend(); ++iter2)
	{

		cout << " £ü " << *iter2 << " £ü " << endl;
	}

	return 0;
}