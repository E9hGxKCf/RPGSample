//GameTask.h
#pragma once

#include <list>
#include <memory>

//タスクの状態を記述する列挙体
enum GAMETASK_CODE
{
	TASK_FAILED,
	TASK_SUCCEEDED,
	TASK_NEXTSCENE,
};

//キャラクター・向き
enum CHARACTER_DIRECTION_TYPE
{
	CHARACTER_DIR_DOWN,
	CHARACTER_DIR_LEFT,
	CHARACTER_DIR_RIGHT,
	CHARACTER_DIR_UP,
};

//キャラクター・動作状態
enum CHARACTER_MOVE_TYPE
{
	CHARACTER_MOVE,
	CHARACTER_STAY,
};

class GameTask
{
public:
	virtual bool Init() = 0;
	virtual GAMETASK_CODE Update() = 0;
	virtual GAMETASK_CODE Draw() = 0;
	virtual bool Exit() = 0;
};

class GameTaskManager : public GameTask
{
protected:
	std::list < std::shared_ptr<GameTask> > TaskList;

public:
	virtual bool Init();
	virtual GAMETASK_CODE Update();
	virtual GAMETASK_CODE Draw();
	virtual bool Exit();

	virtual void EntryTask(std::shared_ptr<GameTask> task);
};

std::shared_ptr<GameTask> CreateMapTask(int num_x, int num_y, int (*map)[]);
std::shared_ptr<GameTask> CreatePlayerTask();
std::shared_ptr<GameTask> CreateEnemyMapTask(int x, int y, int ProcessNum, int Start[], int Time[], CHARACTER_DIRECTION_TYPE Dir[]);

std::shared_ptr<GameTaskManager> CreateCollisionCheck();

std::shared_ptr<GameTask> CreateBattlePlayerTask();