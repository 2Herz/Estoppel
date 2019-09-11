#include "SystemClass.h"

/*
	이 곳은 메인함수 부분인다.

	직접적으로 프로그램이 실행되는 부분이며

	다른 클래스에서 구현된 모든 기능과 인터페이스들을

	실행파일(.exe파일)로 만드는 부분이다.
*/

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