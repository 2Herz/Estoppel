#include "stdafx.h"
#include "Scene_Intro.h"
#include "SceneMgr.h"

Scene_Intro::Scene_Intro()
{
}
Scene_Intro::~Scene_Intro()
{
}
void Scene_Intro::Init(HWND _hWnd)
{
}
void Scene_Intro::Update(float _elapseTime)
{
}

void Scene_Intro::Render(HDC _hdc)
{
	TextOutA(_hdc, 300, 100, "Scene_Intro", strlen("Scene_Intro"));
	TextOutA(_hdc, 320, 130, "郴何备泅ぁぁ", strlen("郴何备泅ぁぁ"));
}

bool Scene_Intro::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case	WM_RBUTTONDOWN:
		SCENE_MGR.SetScene(SCENE_MENU);
		break;

	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case VK_ESCAPE: return true;	break;
		}
	}break;

	}

	return false;
}
