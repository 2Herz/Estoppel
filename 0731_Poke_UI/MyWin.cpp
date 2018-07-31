#include "MyWin.h"

VOID MyWin::Init(HWND _hWnd)
{
	IMG_MGR->SethWnd(_hWnd);

	IMG_MGR->OpenImg("Image/Dialog_00.bmp");
	IMG_MGR->OpenImg("Image/Dialog_01.bmp");
	
	menuUI.Init(_hWnd);
	box.Init(_hWnd);
}

VOID MyWin::Release()
{
	IMG_MGR->Destroy();
}

VOID MyWin::Update(float _elapseTime)
{

}

VOID MyWin::Render(HDC _hdc)
{
	menuUI.RenderMenu(_hdc);
}

LRESULT MyWin::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_MOUSEMOVE:
	{
		m_MousePos.x = GET_X_LPARAM(_lParam);
		m_MousePos.y = GET_Y_LPARAM(_lParam);
	}break;
	}
	return WinBase::WndProc(_hWnd, _message, _wParam, _lParam);
}

MyWin::MyWin()
{
}

MyWin::~MyWin()
{
}