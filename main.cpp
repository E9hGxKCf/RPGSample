#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//画面モードをウィンドウに変更
	ChangeWindowMode(true);

	//描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);

	//Dxライブラリの初期化
	if (DxLib_Init() == -1)
		return -1;

	//ゲームループ
	while (!ProcessMessage())
	{
		//画面初期化
		ClearDrawScreen();

		//裏画面情報を表画面に転送
		ScreenFlip();
	}

	//Dxライブラリの終了処理
	DxLib_End();

	return 0;
}
