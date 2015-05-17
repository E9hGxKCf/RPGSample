//PlayScene.h
#pragma once

#include "IScene.h"

class PlayScene : public IScene
{
public:
	bool Init();
	bool Exec();
	bool Exit();
	std::shared_ptr<IScene> GetNextScene();
};