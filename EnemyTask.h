//EnemyTask.h
#pragma once

#include <DxLib.h>
#include "GameTask.h"
#include "CollisionObject.h"

#include <vector>

typedef struct{
	int StartCount;
	int ProcessCount;
	CHARACTER_DIRECTION_TYPE Direction;
}MoveProcess;

class EnemyTask : public GameTask, public CollisionObject
{
private:
	const int Size_x = 32;
	const int Size_y = 32;
	int counter;
	int CurrentGraph;
	int GraphHandle[4][3];
	CHARACTER_MOVE_TYPE MoveType;
	CHARACTER_DIRECTION_TYPE DirType;

	std::vector<MoveProcess> MoveList;
	int CurrentMove;

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void Stay();

public:
	EnemyTask(int x, int y, int ProcessNum, int Start[], int Time[], CHARACTER_DIRECTION_TYPE Dir[]);
	bool Init();
	GAMETASK_CODE Update();
	GAMETASK_CODE Draw();
	bool Exit();
};