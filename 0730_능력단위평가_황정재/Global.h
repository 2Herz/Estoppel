#undef UNICODE
#pragma once

#include <Windows.h>
#include <windowsx.h>
#include <sstream>
#pragma comment(lib, "winmm.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define WIN_NAME "�ɷ´����� : Ȳ����"

#define WS_OVERLLAPEDWINDOW (WS_OVERLAPPED) | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)