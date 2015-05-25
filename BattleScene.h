//BattleScene.h
#pragma once

#include "IScene.h"
#include "GameTask.h"

class BattleScene : public IScene
{
private:
	bool ExitFlag;
	std::shared_ptr<GameTask> Root;

public:
	BattleScene(std::shared_ptr<GameTask> roottask);
	bool Init();
	bool Exec();
	bool Exit();
	std::shared_ptr<IScene> GetNextScene();
};