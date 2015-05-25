//MapTask.h
#pragma once

#include <DxLib.h>
#include "GameTask.h"

class MapTask : public GameTask
{
private:
	int GraphHandle[400];
	int Map[20][15];

public:
	MapTask(int num_x, int num_y, int(*map)[]);
	bool Init();
	GAMETASK_CODE Update();
	GAMETASK_CODE Draw();
	bool Exit();
};