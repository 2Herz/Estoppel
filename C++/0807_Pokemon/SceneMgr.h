#pragma once
#include "TextUI.h"
#include "BoxUI.h"
#define WIN_WIDTH 960
#define WIN_HEIGHT 640

enum SCENE_TYPE
{
	SCENE_INTRO,
	SCENE_MAIN,
	SCENE_MENU,
	SCENE_DIC,
	SCENE_POKEMON,
	SCENE_INFO,
	SCENE_BAG,
	SCENE_TRAINER,
	SCENE_REPORT,
	SCENE_SETTING,
	SCENE_BATTLE
};

class Scene;

class SceneMgr
	: public TemplateSingletonA<SceneMgr>
{
	friend TemplateSingletonA;
private:
	Scene			*m_pScene	= nullptr;
	SCENE_TYPE		m_SceneType = SCENE_MAIN;
	bool			m_isChange	= true;
	BoxUI			m_box;
	ImgClass		m_tempScreen;

private:
	SceneMgr();
	~SceneMgr();

	void	ChangeScene();

public:
	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	//	씬 타입 얻기 및 변환
	void		SetScene(SCENE_TYPE _type)
	{
		m_SceneType = _type;
		m_isChange	= true;
	}
	SCENE_TYPE	GetScene()
	{
		return m_SceneType;
	}
	void SetScreen(HDC _hdc)
	{
		BitBlt(m_tempScreen.GetImgDC(), 0, 0, WIN_WIDTH, WIN_HEIGHT, _hdc, 0, 0, SRCCOPY);
	}
	HDC GetScreen()
	{
		return m_tempScreen.GetImgDC();
	}
};

#define		SCENE_MGR		SceneMgr::GetInstance()