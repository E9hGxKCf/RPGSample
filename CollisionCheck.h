//CollisionCheck.h
#pragma once

#include <DxLib.h>
#include "GameTask.h"

class CollisionCheck : public GameTaskManager
{
public:
	GAMETASK_CODE Update();
};