#pragma once
#include "stdafx.h"

class D3DClass : public AlignedAllocationPolicy<16>
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

public:
	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	Device* GetDevice();
	DC* GetDC();

	void GetProjection(XMMATRIX&);
	void GetWorld(XMMATRIX&);
	void GetOrtho(XMMATRIX&);

	void GetVideoCardInfo(char*, int&);

private:
	bool m_vsync_enabled = false;
	int m_videoCardMemory = 0;
	char m_videoCardDesc[128] = {};
	SwapChain* m_SwapChain = nullptr;
	Device* m_Device = nullptr;
	DC* m_pImm = nullptr;
	RTV* m_RTV = nullptr;
	DepthStencil* m_ds = nullptr;
	DepthStencilState* m_dss = nullptr;
	DepthStencilView* m_dv = nullptr;
	RasterizerState* m_rs = nullptr;
	XMMATRIX m_Proj;
	XMMATRIX m_World;
	XMMATRIX m_Ortho;
};
