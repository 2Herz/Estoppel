// 버퍼, 쉐이더 및 HLSL.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "System.h"

int APIENTRY wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR CmdParam, int CmdShow)
{
	//	System 객체 생성
	System* system = new System;
	if (!system)
	{
		return -1;
	}

	//	System 객체 초기화 및 실행
	if (system->Initialize())
	{
		system->Run();
	}

	//	System 객체 종료 및 메모리 반환
	system->Shutdown();
	delete system;
	system = nullptr;

	return 0;
}