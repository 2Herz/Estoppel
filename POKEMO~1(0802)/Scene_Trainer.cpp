#include "stdafx.h"
#include "Scene_Trainer.h"
#include "SceneMgr.h"


Scene_Trainer::Scene_Trainer()
{
}


Scene_Trainer::~Scene_Trainer()
{
}

void Scene_Trainer::Init(HWND _hWnd)
{
}

void Scene_Trainer::Update(float _elapseTime)
{
}

void Scene_Trainer::Render(HDC _hdc)
{
	TextOutA(_hdc, 300, 100, "Scene_Trainer", strlen("Scene_Trainer"));
	TextOutA(_hdc, 320, 130, "郴何备泅ぁぁ", strlen("郴何备泅ぁぁ"));
}

bool Scene_Trainer::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case 'x':
		case 'X': {	SCENE_MGR.SetScene(SCENE_INTRO); }break;

		case VK_ESCAPE: return true;	break;
		}
	}break;

	}
	return false;
}
