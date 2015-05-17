//TitleScene.cpp
#include "TitleScene.h"

std::shared_ptr<IScene> CreateTitleScene()
{
	return std::make_shared<TitleScene>();
}

bool TitleScene::Init()
{
	return true;
}

bool TitleScene::Exec()
{
	OutputDebugString("TitleScene::Exec()\n");

	if (CheckHitKey(KEY_INPUT_Z) == 1)
		return false;

	return true;
}

std::shared_ptr<IScene> TitleScene::GetNextScene()
{
	return CreatePlayScene();
}

bool TitleScene::Exit()
{
	return true;
}

