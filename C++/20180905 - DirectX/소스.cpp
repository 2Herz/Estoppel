#include <windows.h>

CONST INT WIN_WIDTH = 800;
CONST INT WIN_HEIGHT = 600;

//	�������̽� ������ ���� ���Ǽ� �Լ����ø�
template <typename T>
void SafeRelease(T *_p)
{
	if (_p != nullptr)
	{
		_p->Release();
		_p = nullptr;
	}
}

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <DirectXColors.h>
using namespace DirectX;

ID3D11Device *g_pD3DDevice = nullptr;		//	�׷���ī��
ID3D11DeviceContext *g_pImm = nullptr;		//	�׸��� ��
IDXGISwapChain *g_pSwapChain = nullptr;		//	��ȭ��
ID3D11RenderTargetView *g_pRTV = nullptr;	//	ĵ����

VOID Release()
{
	//	������ ������ �������� �����Ѵ�.
	SafeRelease(g_pRTV);
	SafeRelease(g_pImm);
	SafeRelease(g_pSwapChain);
	SafeRelease(g_pD3DDevice);
}

VOID Render(HWND _hWnd)
{
	g_pImm->ClearRenderTargetView(g_pRTV, Colors::Blue);

	//	������ºκ��̴�.
	g_pSwapChain->Present(0, 0);
}

HRESULT InitBase(HWND _hWnd)
{
	//	DX11�� ��ȯ������ HRESULT �ڷ����̴�.
	HRESULT	hr = S_OK;

	//	����ü���� ������ ���� ����ü�̴�.
	//	����ü���� �����ϱ� �����̴�.
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

	//	ȣȯ��
	//	���� ���� �������� ���ʴ�� ȣȯ���� üũ�Ѵ�.
	D3D_FEATURE_LEVEL	FeautureArray[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// ����̽� ����ü�� ������ġ
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,								//	�����(�����)
		D3D_DRIVER_TYPE_HARDWARE,				//	�ϵ����Ӱ���
		nullptr,								//	
		D3D11_CREATE_DEVICE_SINGLETHREADED,		//	�ɼ�
		FeautureArray,							//	����DX ���� �迭
		ARRAYSIZE(FeautureArray),				//	���� �迭 ����
		D3D11_SDK_VERSION,						//	SDK ����
		&sd,									//	����ü�� ���� ����ü
		&g_pSwapChain,							//	������ ����ü�� �ּ� ����
		&g_pD3DDevice,							//	������ ����̽� �ּ� ����
		nullptr,								//	Ȯ���� ���� ����
		&g_pImm);								//	������ ������ġ �ּ� ����

	if (FAILED(hr))
		return hr;

	// ����Ÿ�� �����
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
		return hr;

	hr = g_pD3DDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRTV);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	g_pImm->OMSetRenderTargets(1, &g_pRTV, nullptr);

	// ����Ʈ ����
	D3D11_VIEWPORT vp = {};
	vp.Width = (FLOAT)WIN_WIDTH;
	vp.Height = (FLOAT)WIN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImm->RSSetViewports(1, &vp);

	return hr;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return(DefWindowProc(hWnd, message, wParam, lParam));
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdParam, int CmdShow)
{
	WNDCLASSA	WndClass = {};

	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursorA(nullptr, IDC_ARROW);
	WndClass.hIcon = LoadIconA(nullptr, IDI_APPLICATION);
	WndClass.hInstance = hInst;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = "KMK";
	WndClass.lpszMenuName = nullptr;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	������ Ŭ���� ���
	RegisterClassA(&WndClass);

	//	���� ������ ũ�� ���
	RECT	WinRt = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	AdjustWindowRect(&WinRt, WS_OVERLAPPEDWINDOW, FALSE);

	// ���� �ʿ��� ���μ��� ���ϱ�
	int Width = WinRt.right - WinRt.left;
	int Height = WinRt.bottom - WinRt.top;

	//	������ ����
	HWND hWnd = CreateWindowExA(0, WndClass.lpszClassName, "KMKSAMPLE", WS_OVERLAPPEDWINDOW, 0, 0, Width, Height, nullptr, (HMENU)nullptr, hInst, nullptr);

	if (hWnd == nullptr)
	{
		MessageBoxA(nullptr, "��������� ����", "����", MB_OK);
		return 0;
	}

	//	������â ȭ�鿡 �����ֱ�
	ShowWindow(hWnd, CmdShow);

	//	�ʱ�ȭ
	if (FAILED(InitBase(hWnd)))
	{
		MessageBoxA(nullptr, "�ʱ�ȭ ����", "����", MB_OK);
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

	return Message.wParam;
}