#pragma once
#include <Windows.h>
#include "SingletonA.h"

enum SCENE_TYPE
{
	SCENE_INTRO,
	SCENE_MAIN,
	SCENE_END
};

class Scene;

class SceneMgr : public SingletonA<SceneMgr>
{
	friend SingletonA;
private:
	Scene * m_pScene = nullptr;
	SCENE_TYPE		m_SceneType = SCENE_INTRO;
	bool			m_isChange = true;

private:
	SceneMgr();
	~SceneMgr();

	void	ChangeScene();

public:
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	//	씬 타입 얻기 및 변환
	void		SetScene(SCENE_TYPE _type)
	{
		m_SceneType = _type;
		m_isChange = true;
	}
	SCENE_TYPE	GetScene()
	{
		return m_SceneType;
	}
};

#define		SCENE_MGR		SceneMgr::GetInst()

