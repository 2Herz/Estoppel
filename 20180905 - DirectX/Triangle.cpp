#include <Windows.h>

CONST INT WIN_WIDTH = 800;
CONST INT WIN_HEIGHT = 800;

template <typename T>
void SafeRelease(T &_p)
{
	if (_p != nullptr)
	{
		_p->Release();
		_p = nullptr;
	}
}

#include <d3d11.h>
#include <d3dcommon.h>
#include <DirectXColors.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
using namespace DirectX;

ID3D11Device			*g_pD3DDevice = nullptr;
ID3D11DeviceContext		*g_pImm = nullptr;
IDXGISwapChain			*g_pSwapChain = nullptr;
ID3D11RenderTargetView	*g_pRTV = nullptr;

struct SimpleVertex
{
	XMFLOAT3	Pos;
};

struct SimpleVertex2
{
	XMFLOAT3	Pos2;
};

//	실제 정점 정보들
ID3D11Buffer			*g_pVertexBuffer = nullptr;

//	정점셰이더에 들어가는 정점 한개의 형태( 구조체 정보라고 생각 )
ID3D11InputLayout		*g_pInputLayout = nullptr;

//	정점셰이더
ID3D11VertexShader		*g_pVertexShader = nullptr;
//	픽셀셰이더
ID3D11PixelShader		*g_pPixelShader = nullptr;

HRESULT	InitBase(HWND _hWnd)
{
	HRESULT	hr = S_OK;

	DXGI_SWAP_CHAIN_DESC	sd = {};

	sd.BufferCount = 1;
	sd.BufferDesc.Width = WIN_WIDTH;
	sd.BufferDesc.Height = WIN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.OutputWindow = _hWnd;
	sd.Windowed = TRUE;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;


	D3D_FEATURE_LEVEL	FeautureArray[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// 디바이스 스왑체인 문맥장치
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_SINGLETHREADED, FeautureArray, ARRAYSIZE(FeautureArray), D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pD3DDevice, nullptr, &g_pImm);

	if (FAILED(hr))
		return hr;

	// 랜더타겟 만들기
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
		return hr;

	hr = g_pD3DDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRTV);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	g_pImm->OMSetRenderTargets(1, &g_pRTV, nullptr);

	// Setup the viewport
	D3D11_VIEWPORT vp = {};
	vp.Width = (FLOAT)WIN_WIDTH;
	vp.Height = (FLOAT)WIN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImm->RSSetViewports(1, &vp);

	//	정점
	//	실제 정점 데이터
	SimpleVertex	vertives[] =
	{
		XMFLOAT3(0.5f, 0.5f, 0.5f),
		XMFLOAT3(0.5f, -0.5f, 0.5f),
		XMFLOAT3(-0.5f, -0.5f, 0.5f),
		XMFLOAT3(0.5f, 0.5f, 0.5f),
		XMFLOAT3(-0.5f, -0.5f, 0.5f),
		XMFLOAT3(-0.5f, 0.5f, 0.5f),
	};

	// 버퍼 정보
	D3D11_BUFFER_DESC		bd = {};
	bd.ByteWidth = sizeof(SimpleVertex) * ARRAYSIZE(vertives);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// 실제 데이터 주소
	D3D11_SUBRESOURCE_DATA	InitData = {};
	InitData.pSysMem = vertives;

	hr = g_pD3DDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);

	ID3DBlob	*pBlob = nullptr;

	//	정점 셰이더
	hr = D3DCompileFromFile(L"Sample.fx", nullptr, nullptr, "VS","vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &pBlob, nullptr);

	if (FAILED(hr))	return hr;

	hr = g_pD3DDevice->CreateVertexShader(
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		nullptr,
		&g_pVertexShader);

	if (FAILED(hr))
	{
		pBlob->Release();
		return hr;
	}

	//	입력 레이아웃
	D3D11_INPUT_ELEMENT_DESC	layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hr = g_pD3DDevice->CreateInputLayout(
		layout,
		ARRAYSIZE(layout),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&g_pInputLayout);

	pBlob->Release();

	if (FAILED(hr))	return hr;

	//	픽셀 셰이더
	//	정점 셰이더
	hr = D3DCompileFromFile(L"Sample.fx", nullptr, nullptr, "PS", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &pBlob, nullptr);

	if (FAILED(hr))	return hr;

	hr = g_pD3DDevice->CreatePixelShader(
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		nullptr,
		&g_pPixelShader);

	pBlob->Release();

	return hr;
}

VOID	Release()
{
	SafeRelease(g_pVertexBuffer);
	SafeRelease(g_pInputLayout);
	SafeRelease(g_pVertexShader);
	SafeRelease(g_pPixelShader);

	SafeRelease(g_pRTV);
	SafeRelease(g_pImm);
	SafeRelease(g_pSwapChain);
	SafeRelease(g_pD3DDevice);
}

VOID	Render(HWND _hWnd)
{
	g_pImm->ClearRenderTargetView(g_pRTV, Colors::Blue);

	if (g_pVertexBuffer != nullptr && g_pInputLayout != nullptr && g_pVertexShader != nullptr && g_pPixelShader != nullptr)
	{
		g_pImm->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		UINT Stride = sizeof(SimpleVertex);
		UINT Offset = 0;
		g_pImm->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &Stride, &Offset);

		g_pImm->IASetInputLayout(g_pInputLayout);

		g_pImm->VSSetShader(g_pVertexShader, nullptr, 0);
		g_pImm->PSSetShader(g_pPixelShader, nullptr, 0);

		g_pImm->Draw(6, 0);
	}

	g_pSwapChain->Present(0, 0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	WNDCLASSA	WndClass = {};

	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursorA(nullptr, IDC_ARROW);
	WndClass.hIcon = LoadIconA(nullptr, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = "KMK";
	WndClass.lpszMenuName = nullptr;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassA(&WndClass);

	RECT	WinRt = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	AdjustWindowRect(&WinRt, WS_OVERLAPPEDWINDOW, FALSE);

	int Width = WinRt.right - WinRt.left;
	int Height = WinRt.bottom - WinRt.top;

	HWND hWnd = CreateWindowExA(0, WndClass.lpszClassName, "KMKSAMPLE", WS_OVERLAPPEDWINDOW, 0, 0, Width, Height, nullptr, (HMENU)nullptr, hInstance, nullptr);	

	if (hWnd == nullptr)
	{
		MessageBoxA(nullptr, "윈도우생성 실패", "오류", MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);

	if (FAILED(InitBase(hWnd)))
	{
		MessageBoxA(nullptr, "초기화 실패", "오류", MB_OK);
		return 0;
	}

	MSG	Message;

	while (true)
	{
		if (PeekMessageA(&Message, nullptr, 0U, 0U, PM_REMOVE))
		{
			if (Message.message == WM_QUIT) break;

			TranslateMessage(&Message);
			DispatchMessageA(&Message);
		}
		else
		{
			Render(hWnd);
		}
	}

	Release();

	return static_cast<int>(Message.wParam);
}