#include "SystemClass.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR CmdParam, int CmdShow)
{
	SystemClass*	System = nullptr;
	bool result = false;

	//	시스템 객체 생성
	System = new SystemClass;
	if (!System)
	{
		return 0;
	}

	//	시스템 객체 초기화 및 실행
	//	실제 프로그램 구동점
	result = System->Init();
	if (result)
	{
		System->Run();
	}

	//	시스템 오브젝트 종료 및 해제
	System->Shutdown();
	delete System;
	System = nullptr;

	return 0;
}