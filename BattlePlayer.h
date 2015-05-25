//BattlePlayer.h
#pragma once

#include <DxLib.h>
#include "GameTask.h"

class BattlePlayerTask : public GameTask
{
private:
	const int Size_x = 32;
	const int Size_y = 32;
	int counter;
	int CurrentGraph;
	int WindowHandle[4];
	int FrameHandle[8];
	int BackGroundHandle;
	int CharaGraphHandle[4][3];
	int CharaGraphHandle2[4][3];

	CHARACTER_MOVE_TYPE MoveType;
	CHARACTER_DIRECTION_TYPE DirType;

public:
	bool Init();
	GAMETASK_CODE Update();
	GAMETASK_CODE Draw();
	bool Exit();
};