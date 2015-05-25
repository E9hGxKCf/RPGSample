//MapScene.cpp
#include "MapScene.h"
#include "KeyDownChecker.h"

std::shared_ptr<IScene> CreateMapScene()
{
	//マップ情報
	int tmpMap[20][15] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
		{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
		{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
		{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
		{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
		{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
		{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
		{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
		{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	//敵情報
	int PosX[] = {15, 15};
	int PosY[] = {12, 2};
	int Start[][4] = {
		{ 120, 360, 600, 840 },
		{ 120, 360, 600, 840 },
	};
	int Time[][4] = {
		{ 128, 128, 128, 128 },
		{ 128, 128, 128, 128 },
	};
	CHARACTER_DIRECTION_TYPE Dir[][4] = {
		{ CHARACTER_DIR_LEFT, CHARACTER_DIR_RIGHT, CHARACTER_DIR_UP, CHARACTER_DIR_DOWN },
		{ CHARACTER_DIR_DOWN, CHARACTER_DIR_UP, CHARACTER_DIR_LEFT, CHARACTER_DIR_RIGHT },
	};

	//ルートマネージャーを作成
	std::shared_ptr<GameTaskManager> manager = CreateCollisionCheck();

	//タスクを登録
	manager->EntryTask(CreateMapTask(20, 15, (int (*)[])tmpMap));
	manager->EntryTask(CreatePlayerTask());

	//敵情報を登録
	for (int i = 0; i < 2; i++)
		manager->EntryTask(CreateEnemyMapTask(PosX[i], PosY[i], 4, Start[i], Time[i], Dir[i]));

	std::shared_ptr<MapScene> Scene = std::make_shared<MapScene>(manager);
	return Scene;
}

MapScene::MapScene(std::shared_ptr<GameTask> roottask)
{
	Root = roottask;
}

bool MapScene::Init()
{
	OutputDebugString("MapScene::Init()\n");

	ExitFlag = false;

	Root->Init();
	return true;
}

bool MapScene::Exec()
{
//	OutputDebugString("MapScene::Exec()\n");

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

bool MapScene::Exit()
{
	OutputDebugString("MapScene::Exit()\n");

	Root->Exit();
	return true;
}

std::shared_ptr<IScene> MapScene::GetNextScene()
{
	if (ExitFlag)
		return CreateTitleScene();

	return CreateBattleScene();
}