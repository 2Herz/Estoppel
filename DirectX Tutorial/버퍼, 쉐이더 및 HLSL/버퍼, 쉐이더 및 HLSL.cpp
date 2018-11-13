// ����, ���̴� �� HLSL.cpp: ���� ���α׷��� �������� �����մϴ�.
//

#include "stdafx.h"
#include "System.h"

int APIENTRY wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR CmdParam, int CmdShow)
{
	//	System ��ü ����
	System* system = new System;
	if (!system)
	{
		return -1;
	}

	//	System ��ü �ʱ�ȭ �� ����
	if (system->Initialize())
	{
		system->Run();
	}

	//	System ��ü ���� �� �޸� ��ȯ
	system->Shutdown();
	delete system;
	system = nullptr;

	return 0;
}