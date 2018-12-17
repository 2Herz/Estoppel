#include "SceneMgr.h"

//	씬 클래스 포함
#include "Scene_Intro.h"
#include "Scene_Main.h"

///////////////////////////

SceneMgr::SceneMgr()
{
}
SceneMgr::~SceneMgr()
{
	delete m_pScene;
}

void SceneMgr::ChangeScene()
{
	delete m_pScene;

	switch (m_SceneType)
	{
	case SCENE_TYPE::SCENE_INTRO:	m_pScene = new Scene_Intro;			break;
	case SCENE_TYPE::SCENE_MAIN:	m_pScene = new Scene_Main;			break;

	default: break;
	}

	m_isChange = false;
}

void SceneMgr::Update(float _elapseTime)
{
	if (m_isChange == true) ChangeScene();

	if (m_pScene == nullptr) return;

	m_pScene->Update(_elapseTime);
}

void SceneMgr::Render(HDC _hdc)
{
	if (_hdc == nullptr || m_pScene == nullptr) return;

	m_pScene->Render(_hdc);
}

bool SceneMgr::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	if (m_pScene == nullptr) return false;

	return m_pScene->WndProc(_hWnd, _message, _wParam, _lParam);
}
