//PlayScene.h
#pragma once

#include "IScene.h"

class PlayScene : public IScene
{
private:
	enum PLAY_SCENE_TYPE{
		PLAY_SCENE_MAP,
		PLAY_SCENE_BATTLE,
		PLAY_SCENE_ALL
	};
	std::shared_ptr<IScene> ExecScene[PLAY_SCENE_ALL];
	PLAY_SCENE_TYPE ExecSceneType;
	std::shared_ptr<IScene> NextScene;

public:
	PlayScene(std::shared_ptr<IScene> Map, std::shared_ptr<IScene> Battle);
	bool Init();
	bool Exec();
	bool Exit();
	std::shared_ptr<IScene> GetNextScene();
};