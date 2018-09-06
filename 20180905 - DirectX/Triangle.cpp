#include <Windows.h>

CONST INT WIN_WIDTH = 800;
CONST INT WIN_HEIGHT = 800;

//	인터페이스 해제를 위한 편의성 함수템플릿
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

ID3D11Device			*g_pD3DDevice = nullptr;	//	그래픽카드
ID3D11DeviceContext		*g_pImm = nullptr;			//	그리는 놈
IDXGISwapChain			*g_pSwapChain = nullptr;	//	그릴 도화지
ID3D11RenderTargetView	*g_pRTV = nullptr;			//	도화지를 꽂는 캔버스

/*
	g_pD3DDevice를 준비하고 g_pRTV에 g_pSwapChain를 꽂아서 g_pImm이 그린다.
	->	장치를 준비하고 캔버스에 도화지를 꽂아서 그리는 놈이 그린다.
*/

/*
	DX관련 구조체이름에 I가 붙는 이유는 Interface(인터페이스)를 가리키기 때문이다.

	DX관련 구조체 or 클래스들은 포인터로만 변수 선언을 허락한다.
*/

//	모델 그리기용 인터페이스
struct SimpleVertex
{
	XMFLOAT3	Pos;
};

struct SimpleVertex2
{
	XMFLOAT3X3 Pos;
};

//	실제 정점 정보들
ID3D11Buffer			*g_pVertexBuffer = nullptr;

//	정점셰이더에 들어가는 정점 한개의 형태( 구조체 정보라고 생각 )
ID3D11InputLayout		*g_pInputLayout = nullptr;

//	정점셰이더
ID3D11VertexShader		*g_pVertexShader = nullptr;
//	픽셀셰이더
ID3D11PixelShader		*g_pPixelShader = nullptr;

/*
Vertex vs 3DPoint

3DPoint : 3차원 가상공간의 위치 정보( x, y, z )
Vertex	: 위치, 법선, 색상, UV 등 정보를 정보체
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

	//	디바이스 스왑체인 문맥장치
	//	어댑터(모니터), 하드웨어가속관련, x, 옵션, 지원 DX 레벨 배열, SDK 버전, 스왑체인 정보 구조체, 생성된 스왑체인 주소 저장, 생성된 디바이스 주소 저장, 확정된 레벨 정보, 생성된 문맥장치 주소 저장, 
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

	// 뷰포트 설정
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
		XMFLOAT3(0.5f, 0.5f, 0),
		XMFLOAT3(0.5f, -0.5f, 0),
		XMFLOAT3(-0.5f, -0.5f, 0),


		XMFLOAT3(0.5f, 0.5f, 0),
		XMFLOAT3(-0.5f, -0.5f, 0),
		XMFLOAT3(-0.5f, 0.5f, 0),
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
	//	정점관련 해제
	SafeRelease(g_pVertexBuffer);
	SafeRelease(g_pInputLayout);
	SafeRelease(g_pVertexShader);
	SafeRelease(g_pPixelShader);

	//	해제
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
		//	점 표현 방법(점, 선, 삼각형)
		g_pImm->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//	버텍스 구조체의 크기
		UINT Stride = sizeof(SimpleVertex);
		UINT Offset = 0;
		g_pImm->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &Stride, &Offset);

		//	입력 레이아웃
		g_pImm->IASetInputLayout(g_pInputLayout);

		//	셰이더들
		g_pImm->VSSetShader(g_pVertexShader, nullptr, 0);	//	버텍스 셰이더(정점 셰이더)
		g_pImm->PSSetShader(g_pPixelShader, nullptr, 0);	//	픽셀 셰이더

		//	그리기
		g_pImm->Draw(6, 0);
	}

	//	최종출력
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
	//	윈도우 클래스의 정보를 입력
	WNDCLASSA	WndClass = {};

	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursorA(nullptr, IDC_ARROW);
	WndClass.hIcon = LoadIconA(nullptr, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = "KMK";
	WndClass.lpszMenuName = nullptr;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	윈도우 클래스를 등록
	RegisterClassA(&WndClass);

	//	실제 윈도우의 크기를 계산
	RECT	WinRt = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	AdjustWindowRect(&WinRt, WS_OVERLAPPEDWINDOW, FALSE);

	//	실제로 필요한 가로와 세로 구하기
	int Width = WinRt.right - WinRt.left;
	int Height = WinRt.bottom - WinRt.top;

	//	윈도우 생성 : Ex스타일, 클래스명, 윈도우 타이틀, 창 특성, 시작 위치, 크기, 부모윈도우, 메뉴, 연결할 프로세스, 무쓸모
	HWND hWnd = CreateWindowExA(0, WndClass.lpszClassName, "KMKSAMPLE", WS_OVERLAPPEDWINDOW, 0, 40, Width, Height, nullptr, (HMENU)nullptr, hInstance, nullptr);	

	//	윈도우를 생성에 실패했을 경우 발생되는 메세지이다.
	if (hWnd == nullptr)
	{
		MessageBoxA(nullptr, "윈도우생성 실패", "오류", MB_OK);
		return 0;
	}

	//	윈도우창 화면에 보여주기
	ShowWindow(hWnd, nCmdShow);

	//	초기화
	//	DirectX 초기화에 실패했을 경우 발생되는 메세지이다.
	if (FAILED(InitBase(hWnd)))
	{
		MessageBoxA(nullptr, "초기화 실패", "오류", MB_OK);
		return 0;
	}

	//	메세지 루프
	MSG	Message;

	while (true)
	{
		//	메세지가 발생했을때 처리하는 부분이다.
		//	메세지가 발생했다면 while문에서 if문으로 들어가서 발생한 메세지를 처리하고 메세지가 발생하지 않았다면 윈도우의 데드타임이므로 그 부분에서 Render함수를 호출하게 된다.
		if (PeekMessageA(&Message, nullptr, 0U, 0U, PM_REMOVE))
		{
			if (Message.message == WM_QUIT) break;	//	종료

			TranslateMessage(&Message);				//	WM_CHAR 발생용
			DispatchMessageA(&Message);				//	콜백함수 호출
		}
		else
		{
			Render(hWnd);
		}
	}

	//	해제
	Release();

	return static_cast<int>(Message.wParam);
}