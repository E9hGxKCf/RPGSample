//IScene.h
#pragma once

#include <memory>
#include <DxLib.h>

class IScene
{
public:
	virtual bool Init() = 0;
	virtual bool Exec() = 0;
	virtual bool Exit() = 0;
	virtual std::shared_ptr<IScene> GetNextScene() = 0;
};

std::shared_ptr<IScene> CreateTitleScene();
std::shared_ptr<IScene> CreateBattleScene();
std::shared_ptr<IScene> CreateMapScene();