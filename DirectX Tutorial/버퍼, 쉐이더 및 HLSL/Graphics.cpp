#include "stdafx.h"
#include "D3DClass.h"
#include "Camera.h"
#include "Model.h"
#include "ColorShader.h"
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

	m_Camera = new Camera;
	if (!m_Camera)
	{
		return false;
	}

	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

	m_Model = new Model;
	if (!m_Model)
	{
		return false;
	}

	if (!m_Model->Initialize(m_Direct3D->GetDevice()))
	{
		MessageBox(hWnd, L"모델 오브젝트를 초기화하지 못했습니다!", L"오류", MB_OK);
		return false;
	}

	m_ColorShader = new ColorShader;
	if (!m_ColorShader)
	{
		return false;
	}

	if (!m_ColorShader->Initialize(m_Direct3D->GetDevice(), hWnd))
	{
		MessageBox(hWnd, L"ColorShader 오브젝트를 초기화하지 못했습니다!", L"오류", MB_OK);
		return false;
	}

	return true;
}

void Graphics::Shutdown()
{
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
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

	m_Camera->Render();

	XMMATRIX world, view, projection;
	m_Direct3D->GetWorld(world);
	m_Camera->GetViewMatrix(view);
	m_Direct3D->GetProjection(projection);

	m_Model->Render(m_Direct3D->GetDC());

	if (!m_ColorShader->Render(m_Direct3D->GetDC(),
		m_Model->GetIndexCount(), world, view, projection))
	{
		return false;
	}

	m_Direct3D->EndScene();

	return true;
}