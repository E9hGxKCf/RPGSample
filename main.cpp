#include "DxLib.h"

#include "IScene.h"
#include "KeyDownChecker.h"

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
	std::shared_ptr<IScene> ExecScene = CreateBattleScene();// CreateMapScene();// CreateTitleScene();
	ExecScene->Init();

	//キー入力チェッククラスを作成
	KeyDownChecker* Checker = KeyDownChecker::GetInstance();

/*
#include <memory>
#include "MapTask.h"
#include "PlayerTask.h"
#include "EnemyTask.h"

	std::shared_ptr<MapTask> task = std::make_shared<MapTask>();
	std::shared_ptr<PlayerTask> task2 = std::make_shared<PlayerTask>();
	std::shared_ptr<EnemyTask> task3 = std::make_shared<EnemyTask>();
	task->Init();
	task2->Init();
	task3->Init();*/

	//ゲームループ
	while (!ProcessMessage())
	{
		//画面初期化
		ClearDrawScreen();

		//キー入力
		Checker->CheckKeyState();

	/*	task->Update();
		task2->Update();
		task3->Update();

		task->Draw();
		task2->Draw();
		task3->Draw();*/

		//シーンを実行する
		if (!ExecScene->Exec())
		{
			ExecScene->Exit();

			//次のシーンを取得
			ExecScene = ExecScene->GetNextScene();
			ExecScene->Init();
		}/**/

		//裏画面情報を表画面に転送
		ScreenFlip();
	}

/*	task->Exit();
	task2->Exit();
	task3->Exit();*/

	//シーンの終了処理
	ExecScene->Exit();

	//Dxライブラリの終了処理
	DxLib_End();

	return 0;
}
