#include "PlayerTask.h"
#include "KeyDownChecker.h"

std::shared_ptr<GameTask> CreatePlayerTask()
{
	return std::make_shared<PlayerTask>();
}

PlayerTask::PlayerTask()
{
	r = 10;
	id = OBJECT_PLAYER;
}

bool PlayerTask::Init()
{
	x = 4.0f * (float)Size_x;
	y = 2.0f * (float)Size_y;

	int tmp[12];
	LoadDivGraph("Data/Character/Player.png", 12, 3, 4, Size_x, Size_y, tmp);
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 4; y++)
			GraphHandle[y][x] = tmp[3 * y + x];

	MoveType = CHARACTER_STAY;
	DirType = CHARACTER_DIR_DOWN;

	counter = 0;

	return true;
}

GAMETASK_CODE PlayerTask::Update()
{
	//キャラ方向を設定
	if (KeyDownChecker::GetKeyDownState(KEY_INPUT_LEFT))
	{
		DirType = CHARACTER_DIR_LEFT;
	}
	else if (KeyDownChecker::GetKeyDownState(KEY_INPUT_UP))
	{
		DirType = CHARACTER_DIR_UP;
	}
	else if (KeyDownChecker::GetKeyDownState(KEY_INPUT_RIGHT))
	{
		DirType = CHARACTER_DIR_RIGHT;
	}
	else if (KeyDownChecker::GetKeyDownState(KEY_INPUT_DOWN))
	{
		DirType = CHARACTER_DIR_DOWN;
	}

	//キャラ移動
	if (KeyDownChecker::GetKeyState(KEY_INPUT_LEFT)	 ||
		KeyDownChecker::GetKeyState(KEY_INPUT_UP)	 ||
		KeyDownChecker::GetKeyState(KEY_INPUT_RIGHT) ||
		KeyDownChecker::GetKeyState(KEY_INPUT_DOWN)
		)
	{
		counter++;
		MoveType = CHARACTER_MOVE;

		if (counter % 20 == 1)
			CurrentGraph = (CurrentGraph == 0 ? 2 : 0);

		//座標の移動
		switch (DirType)
		{
			case CHARACTER_DIR_LEFT:
				x--;
				break;
			case CHARACTER_DIR_RIGHT:
				x++;
				break;
			case CHARACTER_DIR_UP:
				y--;
				break;
			case CHARACTER_DIR_DOWN:
				y++;
				break;
		}

		//画面外判定
		if (x < -Size_x)
			x = 640;
		else if (x > 640)
			x = (float)-Size_x;

		if (y < -Size_y)
			y = 480;
		else if (y > 480)
			y = (float)-Size_y;

	}
	else
	{
		counter = 0;
		MoveType = CHARACTER_STAY;

		CurrentGraph = 1;
	}

	return TASK_SUCCEEDED;
}

GAMETASK_CODE PlayerTask::Draw()
{
	DrawGraphF(x, y, GraphHandle[DirType][CurrentGraph], true);

	return TASK_SUCCEEDED;
}

bool PlayerTask::Exit()
{
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 3; y++)
			 DeleteGraph(GraphHandle[x][y]);

	return true;
}