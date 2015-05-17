#include "DxLib.h"
#include "IScene.h"

class KeyChecker
{
private:
	char Buf[256];
	char StateBuf[256];

public:
	KeyChecker()
	{
		ZeroMemory(Buf, sizeof(char) * 256);
		ZeroMemory(StateBuf, sizeof(char) * 256);
	}

	void CheckKeyState()
	{
		GetHitKeyStateAll(StateBuf);

		for (int i = 0; i < 256; i++)
		{
			if (StateBuf[i] == 1)
				Buf[i]++;
			else
				Buf[i] = 0;
		}
	}

	bool GetKeyDown(int KeyCode)
	{
		return (Buf[KeyCode] == 1 ? true : false);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//画面モードをウィンドウに変更
	ChangeWindowMode(true);

	//描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);

	//Dxライブラリの初期化
	if (DxLib_Init() == -1)
		return -1;

	//シーンを取得、初期化する
	std::shared_ptr<IScene> ExecScene = CreateTitleScene();
	ExecScene->Init();

	//ゲームループ
	while (!ProcessMessage())
	{
		//画面初期化
		ClearDrawScreen();

		//シーンを実行する
		if (!ExecScene->Exec())
		{
			ExecScene->Exit();

			//次のシーンを取得
			ExecScene = ExecScene->GetNextScene();
			ExecScene->Init();
		}

		//裏画面情報を表画面に転送
		ScreenFlip();
	}

	//シーンの終了処理
	ExecScene->Exit();

	//Dxライブラリの終了処理
	DxLib_End();

	return 0;
}
