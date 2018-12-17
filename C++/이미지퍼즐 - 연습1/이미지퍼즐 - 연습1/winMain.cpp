#include "Global.h"
#include "My.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR CmdParam, int CmdShow)
{
	My main;

	if (main.NewWin(hInst, WIN_WIDTH, WIN_HEIGHT, WIN_NAME) == FALSE)
	{
		return 0;
	}

	return main.MessageLoop();
}