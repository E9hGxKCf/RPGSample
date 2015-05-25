#include "EnemyTask.h"
#include "KeyDownChecker.h"

std::shared_ptr<GameTask> CreateEnemyMapTask(int x, int y, int ProcessNum, int Start[], int Time[], CHARACTER_DIRECTION_TYPE Dir[])
{
	return std::make_shared<EnemyTask>(x, y, ProcessNum, Start, Time, Dir);
}

void EnemyTask::MoveLeft()
{
	DirType = CHARACTER_DIR_LEFT;
	x--;

	if (counter % 20 == 1)
		CurrentGraph = (CurrentGraph == 0 ? 2 : 0);
}

void EnemyTask::MoveRight()
{
	DirType = CHARACTER_DIR_RIGHT;
	x++;

	if (counter % 20 == 1)
		CurrentGraph = (CurrentGraph == 0 ? 2 : 0);
}

void EnemyTask::MoveUp()
{
	DirType = CHARACTER_DIR_UP;
	y--;

	if (counter % 20 == 1)
		CurrentGraph = (CurrentGraph == 0 ? 2 : 0);
}

void EnemyTask::MoveDown()
{
	DirType = CHARACTER_DIR_DOWN;
	y++;

	if (counter % 20 == 1)
		CurrentGraph = (CurrentGraph == 0 ? 2 : 0);
}

void EnemyTask::Stay()
{
	MoveType = CHARACTER_STAY;
	CurrentGraph = 1;
}

EnemyTask::EnemyTask(int X, int Y, int ProcessNum, int Start[], int Time[], CHARACTER_DIRECTION_TYPE Dir[])
{
	r = 10;
	id = OBJECT_ENEMY;

	x = (float)X * (float)Size_x;//15
	y = (float)Y * (float)Size_y;//12

	for (int i = 0; i < 4; i++)
	{
		MoveProcess Process;
		Process.StartCount = Start[i];
		Process.ProcessCount = Time[i];
		Process.Direction = Dir[i];

		MoveList.push_back(Process);
	}
}

bool EnemyTask::Init()
{
	int tmp[12];
	LoadDivGraph("Data/Character/Enemy.png", 12, 3, 4, Size_x, Size_y, tmp);
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 4; y++)
			GraphHandle[y][x] = tmp[3 * y + x];

	MoveType = CHARACTER_STAY;
	DirType = CHARACTER_DIR_DOWN;

	counter = 0;
	CurrentGraph = 1;
	CurrentMove = 0;

	return true;
}

GAMETASK_CODE EnemyTask::Update()
{
	if (MoveList[CurrentMove].StartCount <= counter)
	{
		//終了処理
		if (MoveList[CurrentMove].ProcessCount + MoveList[CurrentMove].StartCount == counter)
		{
			CurrentMove++;
			if (CurrentMove == MoveList.size())
			{
				CurrentMove = 0;
				counter = -1;	//最後なのでカウンタを-1に戻す
			}
		}
		else
		{
			//移動操作
			switch (MoveList[CurrentMove].Direction)
			{
				case CHARACTER_DIR_LEFT:
					MoveLeft();
					break;
				case CHARACTER_DIR_RIGHT:
					MoveRight();
					break;
				case CHARACTER_DIR_UP:
					MoveUp();
					break;
				case CHARACTER_DIR_DOWN:
					MoveDown();
					break;
			}
		}
	}
	else	//プロセス時以外は待機
		Stay();
/*	if (counter > 120 && counter < 240)
	{
		MoveLeft();
	}
	else if (counter > 360 && counter < 480)
	{
		MoveRight();
	}
	else if (counter > 600 && counter < 720)
	{
		MoveUp();
	}
	else if (counter > 840 && counter < 960)
	{
		MoveDown();
	}
	else if (counter == 960)
	{
		counter = 0;
	}
	else
	{
		Stay();
	}
/*	//キャラ方向を設定
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
	if (KeyDownChecker::GetKeyState(KEY_INPUT_LEFT) ||
		KeyDownChecker::GetKeyState(KEY_INPUT_UP) ||
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
			x = -Size_x;

		if (y < -Size_y)
			y = 480;
		else if (y > 480)
			y = -Size_y;

	}
	else
	{
		counter = 0;
		MoveType = CHARACTER_STAY;

		CurrentGraph = 1;
	}*/

	counter++;

	return TASK_SUCCEEDED;
}

GAMETASK_CODE EnemyTask::Draw()
{
	DrawGraphF(x, y, GraphHandle[DirType][CurrentGraph], true);

	return TASK_SUCCEEDED;
}

bool EnemyTask::Exit()
{
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 3; y++)
			DeleteGraph(GraphHandle[x][y]);

	return true;
}
