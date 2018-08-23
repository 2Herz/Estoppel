#pragma once

#include <Windows.h>
#include <windowsx.h>

#include "FPOINT.h"
#include "Monster.h"
#include <cmath>

#pragma comment(lib, "winmm.lib")

LPCSTR		g_winName	= "HOW-TESTWINDOW";
const int	WIN_WIDTH	= 800;
const int	WIN_HEIGHT	= 600;

extern FPOINT g_PlayerPos;