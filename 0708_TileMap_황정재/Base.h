#pragma once

#include <Windows.h>
#include <string>
using namespace std;

class Base
{
protected:
	string		m_WinName;
	string		m_ClassName;
	SIZE		m_WinSize;
	HINSTANCE	m_hInst;
	HWND		m_hWnd;

private:
	VOID RegWin();
	BOOL CreateWin();
	friend LRESULT CALLBACK	MyWndProc(HWND, UINT, WPARAM, LPARAM);

protected:
	virtual VOID	Init(HWND hWnd);
	virtual VOID	Release();
	virtual VOID	Update(float elapseTime);
	virtual VOID	Render(HDC hdc);
	virtual LRESULT	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	virtual	~Base() = default;
	BOOL	NewWin(HINSTANCE hInst, int width, int height, LPCSTR winName);
	int		MessageLoop();
};