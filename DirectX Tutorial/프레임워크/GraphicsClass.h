#pragma once

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