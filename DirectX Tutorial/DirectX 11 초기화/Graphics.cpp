#include "stdafx.h"
#include "D3DClass.h"
#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::Graphics(const Graphics& other)
{
}

Graphics::~Graphics()
{
}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hWnd)
{
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	if (!m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED,
		hWnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
	{
		MessageBox(hWnd, L"Direct3D를 초기화 하지 못했습니다!", L"오류", MB_OK);
		return false;
	}

	return true;
}

void Graphics::Shutdown()
{
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		_aligned_free(m_Direct3D);
		m_Direct3D = 0;
	}
}

bool Graphics::Frame()
{
	return Render();
}

bool Graphics::Render()
{
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_Direct3D->EndScene();

	return true;
}