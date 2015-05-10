#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)
		return -1;

	while (!ProcessMessage())
	{
		ClearDrawScreen();

		DrawPixel(320, 240, 0xffff);

		ScreenFlip();
	}

	DxLib_End();

	return 0;
}
