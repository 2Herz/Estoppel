#pragma once

/*
	이 곳은 그래픽(Graphics) 클래스이다.

	이 클래스에서는 직접적으로 그래픽카드를 시스템으로부터 얻어와서

	DirectX 프로그램을 만들어가는 클래스이다.

	이 클래스는 외부장치인 그래픽카드와 연관이 있으며

	앞으로 만들어 나갈 모든 DirectX 11 프로그램의 그래픽적인 요소를 총괄하는 곳이다.
*/

#include "Include.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	bool Init(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
};