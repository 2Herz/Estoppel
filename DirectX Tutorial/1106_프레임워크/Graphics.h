#pragma once

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Graphics
{
private:
	bool Render();

public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

public:
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
};