//TitleScene.h
#pragma once

#include "IScene.h"

class TitleScene : public IScene
{
public:
	bool Init();
	bool Exec();
	bool Exit();
	std::shared_ptr<IScene> GetNextScene();
};