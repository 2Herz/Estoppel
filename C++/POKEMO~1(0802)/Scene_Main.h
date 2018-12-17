#pragma once
#include "Scene.h"
class Scene_Main :
	public Scene
{
public:
	float g_time = 0.0f;
	bool g_isGridMode = false;
	bool g_isMoving = false;
	float g_xOffset = 0.0f;
	float g_yOffset = 0.0f;
	POINT g_prevCamPosition;
	std::stringstream g_posStr;
	POINT g_mousePos;

	ImgClass g_background;
public:
	Scene_Main();
	~Scene_Main();

	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};

