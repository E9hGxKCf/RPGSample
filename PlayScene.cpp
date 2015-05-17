//PlayScene.cpp
#include "PlayScene.h"

std::shared_ptr<IScene> CreatePlayScene()
{
	return std::make_shared<PlayScene>();
}

bool PlayScene::Init()
{
	return true;
}

bool PlayScene::Exec()
{
	OutputDebugString("PlayScene::Exec()\n");

	if (CheckHitKey(KEY_INPUT_Z) == 1)
		return false;

	return true;
}

std::shared_ptr<IScene> PlayScene::GetNextScene()
{
	return CreateTitleScene();
}

bool PlayScene::Exit()
{
	return true;
}

