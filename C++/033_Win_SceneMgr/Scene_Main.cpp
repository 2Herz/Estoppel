#include "Scene_Main.h"



Scene_Main::Scene_Main()
{
}


Scene_Main::~Scene_Main()
{
}

void Scene_Main::Update(float _elapseTime)
{
}

void Scene_Main::Render(HDC _hdc)
{
	TextOutA(_hdc, 100, 100, "이곳은메인", 10);
}

bool Scene_Main::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	return false;
}
