//BattleScene.cpp
#include "BattleScene.h"
#include "KeyDownChecker.h"

std::shared_ptr<IScene> CreateBattleScene()
{
	std::shared_ptr<GameTask> task = CreateBattlePlayerTask();
	return std::make_shared<BattleScene>(task);
}

BattleScene::BattleScene(std::shared_ptr<GameTask> roottask)
{
	Root = roottask;
}

bool BattleScene::Init()
{
	OutputDebugString("BattleScene::Init()\n");
	
	ExitFlag = false;

	Root->Init();
	return true;
}

bool BattleScene::Exec()
{
	OutputDebugString("BattleScene::Exec()\n");

	if (KeyDownChecker::GetKeyDownState(KEY_INPUT_Z))
		return false;

	if (KeyDownChecker::GetKeyDownState(KEY_INPUT_A))
	{
		ExitFlag = true;
		return false;
	}

	bool flag = true;
	GAMETASK_CODE code;

	code = Root->Update();

	if (code)
	{
		switch (code)
		{
		case TASK_NEXTSCENE:
			flag = false;
			break;
		}
	}

	code = Root->Draw();

	if (code)
	{
		switch (code)
		{
		case TASK_NEXTSCENE:
			flag = false;
			break;
		}
	}

	return flag;
}

bool BattleScene::Exit()
{
	OutputDebugString("BattleScene::Exit()\n");

	Root->Exit();
	return true;
}

std::shared_ptr<IScene> BattleScene::GetNextScene()
{
	if (ExitFlag)
		return CreateTitleScene();

	return CreateMapScene();
}