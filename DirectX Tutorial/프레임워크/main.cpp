#include "SystemClass.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR CmdParam, int CmdShow)
{
	SystemClass*	System = nullptr;
	bool result = false;

	//	�ý��� ��ü ����
	System = new SystemClass;
	if (!System)
	{
		return 0;
	}

	//	�ý��� ��ü �ʱ�ȭ �� ����
	//	���� ���α׷� ������
	result = System->Init();
	if (result)
	{
		System->Run();
	}

	//	�ý��� ������Ʈ ���� �� ����
	System->Shutdown();
	delete System;
	System = nullptr;

	return 0;
}