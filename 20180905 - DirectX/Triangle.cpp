#include <Windows.h>

CONST INT WIN_WIDTH = 800;
CONST INT WIN_HEIGHT = 800;

//	�������̽� ������ ���� ���Ǽ� �Լ����ø�
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
#pragma comment(lib, "d3d11.lib")

#include <d3dcommon.h>
#include <DirectXColors.h>

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

ID3D11Device			*g_pD3DDevice = nullptr;	//	�׷���ī��
ID3D11DeviceContext		*g_pImm = nullptr;			//	�׸��� ��
IDXGISwapChain			*g_pSwapChain = nullptr;	//	�׸� ��ȭ��
ID3D11RenderTargetView	*g_pRTV = nullptr;			//	��ȭ���� �ȴ� ĵ����

/*
	g_pD3DDevice�� �غ��ϰ� g_pRTV�� g_pSwapChain�� �ȾƼ� g_pImm�� �׸���.
	->	��ġ�� �غ��ϰ� ĵ������ ��ȭ���� �ȾƼ� �׸��� ���� �׸���.
*/

/*
	DX���� ����ü�̸��� I�� �ٴ� ������ Interface(�������̽�)�� ����Ű�� �����̴�.

	DX���� ����ü or Ŭ�������� �����ͷθ� ���� ������ ����Ѵ�.
*/

//	�� �׸���� �������̽�
struct SimpleVertex
{
	XMFLOAT3	Pos;
};

struct SimpleVertex2
{
	XMFLOAT3X3 Pos;
};

//	���� ���� ������
ID3D11Buffer			*g_pVertexBuffer = nullptr;

//	�������̴��� ���� ���� �Ѱ��� ����( ����ü ������� ���� )
ID3D11InputLayout		*g_pInputLayout = nullptr;

//	�������̴�
ID3D11VertexShader		*g_pVertexShader = nullptr;
//	�ȼ����̴�
ID3D11PixelShader		*g_pPixelShader = nullptr;

/*
Vertex vs 3DPoint

3DPoint : 3���� ��������� ��ġ ����( x, y, z )
Vertex	: ��ġ, ����, ����, UV �� ������ ����ü
*/

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

	//	����̽� ����ü�� ������ġ
	//	�����(�����), �ϵ����Ӱ���, x, �ɼ�, ���� DX ���� �迭, SDK ����, ����ü�� ���� ����ü, ������ ����ü�� �ּ� ����, ������ ����̽� �ּ� ����, Ȯ���� ���� ����, ������ ������ġ �ּ� ����, 
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_SINGLETHREADED, FeautureArray, ARRAYSIZE(FeautureArray), D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pD3DDevice, nullptr, &g_pImm);

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

	//	����
	//	���� ���� ������
	SimpleVertex	vertives[] =
	{
		XMFLOAT3(0.5f, 0.5f, 0),
		XMFLOAT3(0.5f, -0.5f, 0),
		XMFLOAT3(-0.5f, -0.5f, 0),


		XMFLOAT3(0.5f, 0.5f, 0),
		XMFLOAT3(-0.5f, -0.5f, 0),
		XMFLOAT3(-0.5f, 0.5f, 0),
	};

	// ���� ����
	D3D11_BUFFER_DESC		bd = {};
	bd.ByteWidth = sizeof(SimpleVertex) * ARRAYSIZE(vertives);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// ���� ������ �ּ�
	D3D11_SUBRESOURCE_DATA	InitData = {};
	InitData.pSysMem = vertives;

	hr = g_pD3DDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);

	ID3DBlob	*pBlob = nullptr;

	//	���� ���̴�
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

	//	�Է� ���̾ƿ�
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

	//	�ȼ� ���̴�
	//	���� ���̴�
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
	//	�������� ����
	SafeRelease(g_pVertexBuffer);
	SafeRelease(g_pInputLayout);
	SafeRelease(g_pVertexShader);
	SafeRelease(g_pPixelShader);

	//	����
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
		//	�� ǥ�� ���(��, ��, �ﰢ��)
		g_pImm->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//	���ؽ� ����ü�� ũ��
		UINT Stride = sizeof(SimpleVertex);
		UINT Offset = 0;
		g_pImm->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &Stride, &Offset);

		//	�Է� ���̾ƿ�
		g_pImm->IASetInputLayout(g_pInputLayout);

		//	���̴���
		g_pImm->VSSetShader(g_pVertexShader, nullptr, 0);	//	���ؽ� ���̴�(���� ���̴�)
		g_pImm->PSSetShader(g_pPixelShader, nullptr, 0);	//	�ȼ� ���̴�

		//	�׸���
		g_pImm->Draw(6, 0);
	}

	//	�������
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
	//	������ Ŭ������ ������ �Է�
	WNDCLASSA	WndClass = {};

	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursorA(nullptr, IDC_ARROW);
	WndClass.hIcon = LoadIconA(nullptr, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = "KMK";
	WndClass.lpszMenuName = nullptr;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	������ Ŭ������ ���
	RegisterClassA(&WndClass);

	//	���� �������� ũ�⸦ ���
	RECT	WinRt = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	AdjustWindowRect(&WinRt, WS_OVERLAPPEDWINDOW, FALSE);

	//	������ �ʿ��� ���ο� ���� ���ϱ�
	int Width = WinRt.right - WinRt.left;
	int Height = WinRt.bottom - WinRt.top;

	//	������ ���� : Ex��Ÿ��, Ŭ������, ������ Ÿ��Ʋ, â Ư��, ���� ��ġ, ũ��, �θ�������, �޴�, ������ ���μ���, ������
	HWND hWnd = CreateWindowExA(0, WndClass.lpszClassName, "KMKSAMPLE", WS_OVERLAPPEDWINDOW, 0, 40, Width, Height, nullptr, (HMENU)nullptr, hInstance, nullptr);	

	//	�����츦 ������ �������� ��� �߻��Ǵ� �޼����̴�.
	if (hWnd == nullptr)
	{
		MessageBoxA(nullptr, "��������� ����", "����", MB_OK);
		return 0;
	}

	//	������â ȭ�鿡 �����ֱ�
	ShowWindow(hWnd, nCmdShow);

	//	�ʱ�ȭ
	//	DirectX �ʱ�ȭ�� �������� ��� �߻��Ǵ� �޼����̴�.
	if (FAILED(InitBase(hWnd)))
	{
		MessageBoxA(nullptr, "�ʱ�ȭ ����", "����", MB_OK);
		return 0;
	}

	//	�޼��� ����
	MSG	Message;

	while (true)
	{
		//	�޼����� �߻������� ó���ϴ� �κ��̴�.
		//	�޼����� �߻��ߴٸ� while������ if������ ���� �߻��� �޼����� ó���ϰ� �޼����� �߻����� �ʾҴٸ� �������� ����Ÿ���̹Ƿ� �� �κп��� Render�Լ��� ȣ���ϰ� �ȴ�.
		if (PeekMessageA(&Message, nullptr, 0U, 0U, PM_REMOVE))
		{
			if (Message.message == WM_QUIT) break;	//	����

			TranslateMessage(&Message);				//	WM_CHAR �߻���
			DispatchMessageA(&Message);				//	�ݹ��Լ� ȣ��
		}
		else
		{
			Render(hWnd);
		}
	}

	//	����
	Release();

	return static_cast<int>(Message.wParam);
}