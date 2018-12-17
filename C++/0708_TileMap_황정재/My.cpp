#include "My.h"
#include <sstream>
using namespace std;
typedef stringstream Text;

//	초기화
VOID My::Init(HWND hWnd)
{
	SellSize.cx = 225;
	SellSize.cy = 225;
	nx = 25;
	ny = 25;
	IMG_MGR->SethWnd(hWnd);
	//	이미지 크기 225 x 225
	IMG_MGR->OpenImg("Tile.bmp", SellSize.cx * 5, SellSize.cy * 5);

	auto img = IMG_MGR->GetImg("Tile");

	if (img != nullptr)
	{
		img->SetTrans();
		img->SetFrame(3);
	}
}
//	해제
VOID My::Release()
{
	IMG_MGR->Destroy();
}
//	갱신
VOID My::Update(float elapseTime)
{
	//	다루는 윈도우가 만든 윈도우임?
	if (isFocus == false) return;

	//	맵 스크롤
	int speed = 15;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		speed *= 2;
	}

	if (SellSize.cx * nx >= WIN_WIDTH)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			StartTilePos.x += speed;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			StartTilePos.x -= speed;
		}
		//	화면안의 타일맵을 벗어나지 않게 막기
		if (StartTilePos.x > 0) StartTilePos.x = 0;
		if (StartTilePos.x + (SellSize.cx * nx) < WIN_WIDTH) StartTilePos.x = WIN_WIDTH - (SellSize.cx * nx);
	}
	if (SellSize.cy * ny >= WIN_HEIGHT)
	{
		if (GetKeyState(VK_UP) & 0x8000)
		{
			StartTilePos.y += speed;
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			StartTilePos.y -= speed;
		}
		//	화면안의 타일맵을 벗어나지 않게 막기
		if (StartTilePos.y > 0) StartTilePos.y = 0;
		if (StartTilePos.y + (SellSize.cy * ny) < WIN_HEIGHT) StartTilePos.y = WIN_HEIGHT - (SellSize.cy * ny);
	}
}
//	랜더(그리기)
VOID My::Render(HDC hdc)
{
	auto img = IMG_MGR->GetImg("Tile");
	for (int y = 0; y < ny; y++)
	{
		for (int x = 0; x < nx; x++)
		{
			if (y % 4 == 0)
			{
				if (x % 4 == 0)
					img->RenderAni(hdc, 0, (StartTilePos.x + (SellSize.cx * x)), (StartTilePos.y + (SellSize.cy * y)));
				else
					img->RenderAni(hdc, 0, (StartTilePos.x + (SellSize.cx * x)), (StartTilePos.y + (SellSize.cy * y)));
			}
			else
			{
				if(x % 4 != 0)
					img->RenderAni(hdc, 0, (StartTilePos.x + (SellSize.cx * x)), (StartTilePos.y + (SellSize.cy * y)));
				else
					img->RenderAni(hdc, 0, (StartTilePos.x + (SellSize.cx * x)), (StartTilePos.y + (SellSize.cy * y)));
			}
		}
	}

	//	타일맵 칸마다 해당 좌표 표시
	for (int ty = 0; ty < ny; ty++)
	{
		for (int tx = 0; tx < nx; tx++)
		{
			Text coordinate;
			coordinate << "(" << tx << " , " << ty << ")";
			TextOut(hdc, (StartTilePos.x + (SellSize.cx * tx) + 4), (StartTilePos.y + (SellSize.cy * ty) + 4),
				coordinate.str().c_str(), coordinate.str().length());
		}
	}

	int x = ((StartTilePos.x * -1) / (SellSize.cx) + (MousePos.x / SellSize.cx));
	int y = ((StartTilePos.y * -1) / (SellSize.cy) + (MousePos.y / SellSize.cy));
	
	Text mouse;
	mouse << "현재 X 좌표 : " << x << " , " << "현재 Y좌표 : " << y;
	TextOut(hdc, MousePos.x - 100, MousePos.y + 30, mouse.str().c_str(), mouse.str().length());
}

LRESULT My::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_ACTIVATEAPP:
		{
			isFocus = (bool)wParam;
		}break;

		case WM_MOUSEMOVE:
		{
			MousePos.x = GET_X_LPARAM(lParam);
			MousePos.y = GET_Y_LPARAM(lParam);
		}break;
	}
	return Base::WndProc(hWnd, message, wParam, lParam);
}
My::My(){}
My::~My(){}