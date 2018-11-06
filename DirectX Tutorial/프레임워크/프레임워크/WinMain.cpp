#include "stdafx.h"
#include "SystemClass.h"

int APIENTRY wWinMain(_In_ INST hInst, _In_opt_ INST hPrevInst, _In_ LPWSTR CmdParam, _In_ int CmdShow)
{
	// System ��ü ����
	SystemClass* System = new SystemClass;
	if (!System)
	{
		return -1;
	}

	// System ��ü �ʱ�ȭ �� ����
	if (System->Initialize())
	{
		System->Run();
	}

	// System ��ü ���� �� �޸� ��ȯ
	System->Shutdown();
	delete System;
	System = nullptr;

	return 0;
}