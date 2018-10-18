#include <iostream>
#include "TemplateDLL.h"
using namespace std;

int main()
{
	TemplateDLL<int> listInt;
	TemplateDLL<float> listFloat;

	for (float i = 0; i < 100; i++)
	{
		listFloat.push_back(i + 1);
	}

	TemplateDLL<float>::Reverse_iterator iter;

	for (iter = listFloat.rbegin(); iter != listFloat.rend(); ++iter)
	{
		cout << *iter << endl;
	}

	return 0;
}