#include <windows.h>

CONST INT WIN_WIDTH = 800;
CONST INT WIN_HEIGHT = 600;

//	인터페이스 해제를 위한 편의성 함수템플릿
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

ID3D11Device *g_pD3DDevice = nullptr;		//	그래픽카드
ID3D11DeviceContext *g_pImm = nullptr;		//	그리는 놈
IDXGISwapChain *g_pSwapChain = nullptr;		//	도화지
ID3D11RenderTargetView *g_pRTV = nullptr;	//	캔버스

VOID Release()
{
	//	생성한 순서의 역순으로 해제한다.
	SafeRelease(g_pRTV);
	SafeRelease(g_pImm);
	SafeRelease(g_pSwapChain);
	SafeRelease(g_pD3DDevice);
}

VOID Render(HWND _hWnd)
{
	g_pImm->ClearRenderTargetView(g_pRTV, Colors::Blue);

	//	최종출력부분이다.
	g_pSwapChain->Present(0, 0);
}

HRESULT InitBase(HWND _hWnd)
{
	//	DX11의 반환값들은 HRESULT 자료형이다.
	HRESULT	hr = S_OK;

	//	스왑체인의 정보를 담은 구조체이다.
	//	스왑체인을 설정하기 위함이다.
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

	//	호환성
	//	가장 높은 버전부터 차례대로 호환성을 체크한다.
	D3D_FEATURE_LEVEL	FeautureArray[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// 디바이스 스왑체인 문맥장치
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,								//	어댑터(모니터)
		D3D_DRIVER_TYPE_HARDWARE,				//	하드웨어가속관련
		nullptr,								//	
		D3D11_CREATE_DEVICE_SINGLETHREADED,		//	옵션
		FeautureArray,							//	지원DX 레벨 배열
		ARRAYSIZE(FeautureArray),				//	레벨 배열 개수
		D3D11_SDK_VERSION,						//	SDK 버전
		&sd,									//	스왑체인 정보 구조체
		&g_pSwapChain,							//	생성된 스왑체인 주소 저장
		&g_pD3DDevice,							//	생성된 디바이스 주소 저장
		nullptr,								//	확정된 레벨 정보
		&g_pImm);								//	생성된 문맥장치 주소 저장

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

	//	윈도우 클래스 등록
	RegisterClassA(&WndClass);

	//	실제 윈도우 크기 계산
	RECT	WinRt = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	AdjustWindowRect(&WinRt, WS_OVERLAPPEDWINDOW, FALSE);

	// 실제 필요한 가로세로 구하기
	int Width = WinRt.right - WinRt.left;
	int Height = WinRt.bottom - WinRt.top;

	//	윈도우 생성
	HWND hWnd = CreateWindowExA(0, WndClass.lpszClassName, "KMKSAMPLE", WS_OVERLAPPEDWINDOW, 0, 0, Width, Height, nullptr, (HMENU)nullptr, hInst, nullptr);

	if (hWnd == nullptr)
	{
		MessageBoxA(nullptr, "윈도우생성 실패", "오류", MB_OK);
		return 0;
	}

	//	윈도우창 화면에 보여주기
	ShowWindow(hWnd, CmdShow);

	//	초기화
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

	return Message.wParam;
}