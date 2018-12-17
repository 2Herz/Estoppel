#pragma once

#include <Windows.h>
#include <windowsx.h>

#include "FPOINT.h"
#include "Monster.h"
#include <cmath>

#pragma comment(lib, "winmm.lib")

LPCSTR		g_winName	= "HOW - FSM";
const int	WIN_WIDTH	= 1280;
const int	WIN_HEIGHT	= 720;

extern FPOINT g_PlayerPos;