#include "stdafx.h"
#include "Scene_Intro.h"

#include <windowsx.h>
#include "SceneMgr.h"

Scene_Intro::Scene_Intro()
{
}
Scene_Intro::~Scene_Intro()
{
}
void Scene_Intro::Update(float _elapseTime)
{
	m_monster.Update(_elapseTime);
}

void Scene_Intro::Render(HDC _hdc)
{
	m_monster.Render(_hdc);
}

bool Scene_Intro::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_RBUTTONDOWN:
		break;
	}
	return false;
}