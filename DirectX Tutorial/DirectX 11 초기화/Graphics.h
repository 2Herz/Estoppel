#pragma once

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class D3DClass;
class CameraClass;
class ModelClass;
class ColorShaderClass;

class Graphics
{
private:
	D3DClass*			m_Direct3D = nullptr;
	CameraClass*		m_Camera = nullptr;
	ModelClass*			m_Model = nullptr;
	ColorShaderClass*	m_ColorShader = nullptr;

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