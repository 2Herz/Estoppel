#include "stdafx.h"
#include "D3DClass.h"

D3DClass::D3DClass()
{
}

D3DClass::D3DClass(const D3DClass& other)
{
}

D3DClass::~D3DClass()
{
}

bool D3DClass::Initialize(int screenWidth, int screenHeight, bool vsync, HWND hWnd, bool fullscreen, float screenDepth, float screenNear)
{
	m_vsync_enabled = vsync;

	Factory* factory = nullptr;
	if (FAILED(CreateDXGIFactory(__uuidof(Factory), (void**)&factory)))
	{
		return false;
	}

	Adapter* adapter = nullptr;
	if (FAILED(factory->EnumAdapters(0, &adapter)))
	{
		return false;
	}

	Output* output = nullptr;
	if (FAILED(adapter->EnumOutputs(0, &output)))
	{
		return false;
	}

	unsigned int numModes = 0;
	if (FAILED(output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED,
		&numModes, nullptr)))
	{
		return false;
	}

	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		return false;
	}

	if (FAILED(output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED,
		&numModes, displayModeList)))
	{
		return false;
	}

	unsigned int numerator = 0;
	unsigned int denomiator = 0;
	for (unsigned int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)screenWidth)
		{
			if (displayModeList[i].Height == (unsigned int)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denomiator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	DXGI_ADAPTER_DESC adapterDesc;
	if (FAILED(adapter->GetDesc(&adapterDesc)))
	{
		return false;
	}

	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	size_t stringLength = 0;
	if (wcstombs_s(&stringLength, m_videoCardDesc, 128, adapterDesc.Description, 128) != 0)
	{
		return false;
	}

	delete[] displayModeList;
	displayModeList = 0;

	output->Release();
	output = 0;

	adapter->Release();
	adapter = 0;

	factory->Release();
	factory = 0;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	if (m_vsync_enabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denomiator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	if (fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, &m_SwapChain, &m_Device, nullptr, &m_pImm)))
	{
		return false;
	}

	DepthStencil* backBufferPtr = nullptr;
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(DepthStencil), (LPVOID*)&backBufferPtr)))
	{
		return false;
	}

	if (FAILED(m_Device->CreateRenderTargetView(backBufferPtr, nullptr, &m_RTV)))
	{
		return false;
	}

	backBufferPtr->Release();
	backBufferPtr = 0;

	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	if (FAILED(m_Device->CreateTexture2D(&depthBufferDesc, nullptr, &m_ds)))
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	if (FAILED(m_Device->CreateDepthStencilState(&depthStencilDesc, &m_dss)))
	{
		return false;
	}

	m_pImm->OMSetDepthStencilState(m_dss, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	if (FAILED(m_Device->CreateDepthStencilView(m_ds, &depthStencilViewDesc,
		&m_dv)))
	{
		return false;
	}

	m_pImm->OMSetRenderTargets(1, &m_RTV, m_dv);

	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	if (FAILED(m_Device->CreateRasterizerState(&rasterDesc, &m_rs)))
	{
		return false;
	}

	m_pImm->RSSetState(m_rs);

	D3D11_VIEWPORT viewport;
	viewport.Width = (float)screenWidth;
	viewport.Height = (float)screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	m_pImm->RSSetViewports(1, &viewport);

	float fieldOfView = 3.141592654f / 4.0f;
	float screenAspect = (float)screenWidth / (float)screenHeight;

	m_Proj = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);
	m_World = XMMatrixIdentity();
	m_Ortho = XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight, screenNear, screenDepth);
	
	return true;
}

void D3DClass::Shutdown()
{
	if (m_SwapChain)
	{
		m_SwapChain->SetFullscreenState(false, nullptr);
	}

	if (m_rs)
	{
		m_rs->Release();
		m_rs = 0;
	}

	if (m_dv)
	{
		m_dv->Release();
		m_dv = 0;
	}

	if (m_ds)
	{
		m_ds->Release();
		m_ds = 0;
	}

	if (m_RTV)
	{
		m_RTV->Release();
		m_RTV = 0;
	}

	if (m_pImm)
	{
		m_pImm->Release();
		m_pImm = 0;
	}

	if (m_Device)
	{
		m_Device->Release();
		m_Device = 0;
	}

	if (m_SwapChain)
	{
		m_SwapChain->Release();
		m_SwapChain = 0;
	}
}

void D3DClass::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4] = { red, green, blue, alpha };

	m_pImm->ClearRenderTargetView(m_RTV, Colors::Blue);

	m_pImm->ClearDepthStencilView(m_dv, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D3DClass::EndScene()
{
	if (m_vsync_enabled)
	{
		m_SwapChain->Present(1, 0);
	}
	else
	{
		m_SwapChain->Present(0, 0);
	}
}

Device* D3DClass::GetDevice()
{
	return m_Device;
}

DC* D3DClass::GetDC()
{
	return m_pImm;
}

void D3DClass::GetProjection(XMMATRIX& proj)
{
	proj = m_Proj;
}

void D3DClass::GetWorld(XMMATRIX& world)
{
	world = m_World;
}

void D3DClass::GetOrtho(XMMATRIX& ortho)
{
	ortho - m_Ortho;
}

void D3DClass::GetVideoCardInfo(char* cardName, int& memory)
{
	strcpy_s(cardName, 128, m_videoCardDesc);
	memory = m_videoCardMemory;
}