//PlayScene.cpp
#include "PlayScene.h"
#include "KeyDownChecker.h"

std::shared_ptr<IScene> CreatePlayScene()
{
	std::shared_ptr<IScene> Map = CreateMapScene();
	std::shared_ptr<IScene> Battle = CreateBattleScene();

	return std::make_shared<PlayScene>(Map, Battle);
}

PlayScene::PlayScene(std::shared_ptr<IScene> Map, std::shared_ptr<IScene> Battle)
{
	ExecScene[PLAY_SCENE_MAP] = Map;
	ExecScene[PLAY_SCENE_BATTLE] = Battle;

	ExecSceneType = PLAY_SCENE_MAP;

	NextScene = nullptr;
}

bool PlayScene::Init()
{
	return ExecScene[ExecSceneType]->Init();
}

bool PlayScene::Exec()
{
//	if (CheckHitKey(KEY_INPUT_Z) == 1)
//	if (KeyDownChecker::GetKeyDownState(KEY_INPUT_Z))
//		return false;

	bool flag = true;

	//シーンを実行する
	if (!ExecScene[ExecSceneType]->Exec())
	{
		//次のシーンをフラグとする
		NextScene = ExecScene[ExecSceneType]->GetNextScene();
		if (!NextScene)
		{
			//今のシーンの終了処理
			ExecScene[ExecSceneType]->Exit();

			//シーンをインクリメント
			ExecSceneType = static_cast<PLAY_SCENE_TYPE>(ExecSceneType + 1);
			if (PLAY_SCENE_ALL == ExecSceneType)
				ExecSceneType = static_cast<PLAY_SCENE_TYPE>(0);

			//次のシーンを初期化
			ExecScene[ExecSceneType]->Init();
		}
		else
			flag = false;
	}

	return flag;
}

bool PlayScene::Exit()
{
	return ExecScene[ExecSceneType]->Exit();
}

std::shared_ptr<IScene> PlayScene::GetNextScene()
{
	return NextScene;
}