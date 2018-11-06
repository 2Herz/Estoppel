#include "stdafx.h"
#include "SystemClass.h"

int APIENTRY wWinMain(_In_ INST hInst, _In_opt_ INST hPrevInst, _In_ LPWSTR CmdParam, _In_ int CmdShow)
{
	// System 객체 생성
	SystemClass* System = new SystemClass;
	if (!System)
	{
		return -1;
	}

	// System 객체 초기화 및 실행
	if (System->Initialize())
	{
		System->Run();
	}

	// System 객체 종료 및 메모리 반환
	System->Shutdown();
	delete System;
	System = nullptr;

	return 0;
}