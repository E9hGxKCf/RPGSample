//MapScene.h
#pragma once

#include "IScene.h"
#include "GameTask.h"

class MapScene : public IScene
{
private:
	bool ExitFlag;
	std::shared_ptr<GameTask> Root;

public:
	MapScene(std::shared_ptr<GameTask> roottask);
	bool Init();
	bool Exec();
	bool Exit();
	std::shared_ptr<IScene> GetNextScene();
};