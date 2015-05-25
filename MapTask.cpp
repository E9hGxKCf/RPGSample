#include "MapTask.h"

std::shared_ptr<GameTask> CreateMapTask(int num_x, int num_y, int(*map)[])
{
	return std::make_shared<MapTask>(num_x, num_y, map);
}

MapTask::MapTask(int num_x, int num_y, int(*map)[])
{
	memcpy(Map, map, sizeof(int) * num_x * num_y);
}

bool MapTask::Init()
{
	LoadDivGraph("Data/Map/ST-Town-E01.png", 400, 8, 50, 32, 32, GraphHandle);

	return true;
}

GAMETASK_CODE MapTask::Update()
{
	return TASK_SUCCEEDED;
}

GAMETASK_CODE MapTask::Draw()
{
	for (int x = 0; x < 20; x++)
		for (int y = 0; y < 15; y++)
		{
			DrawGraph(32 * x, 32 * y, GraphHandle[Map[x][y]], true);

		/*	DrawLine(32 * x, 0, 32 * x, 480, GetColor(255, 0, 0));
			DrawLine(0, 32 * y, 640, 32 * y, GetColor(255, 0, 0));*/
		}


	return TASK_SUCCEEDED;
}

bool MapTask::Exit()
{
	for (int i = 0; i < 400; i++)
		DeleteGraph(GraphHandle[i]);

	return true;
}