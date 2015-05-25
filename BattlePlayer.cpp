#include "BattlePlayer.h"

std::shared_ptr<GameTask> CreateBattlePlayerTask()
{
	return std::make_shared<BattlePlayerTask>();
}

bool BattlePlayerTask::Init()
{
	int tmp[12];
	LoadDivGraph("Data/Character/Player_Battle.png", 12, 3, 4, Size_x, Size_y, tmp);
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 4; y++)
			CharaGraphHandle[y][x] = tmp[3 * y + x];

	LoadDivGraph("Data/Character/Enemy_Battle.png", 12, 3, 4, Size_x, Size_y, tmp);
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 4; y++)
			CharaGraphHandle2[y][x] = tmp[3 * y + x];

	BackGroundHandle = LoadGraph("Data/Other/bg_jan.jpg");

	LoadDivGraph("Data/Other/Window_d_00.png", 4, 2, 2, 64, 64, WindowHandle);

	FrameHandle[0] = DerivationGraph(0,  0, 16, 16, WindowHandle[1]);
	FrameHandle[1] = DerivationGraph(16, 0, 32, 16, WindowHandle[1]);
	FrameHandle[2] = DerivationGraph(48, 0, 16, 16, WindowHandle[1]);
	FrameHandle[3] = DerivationGraph(0, 16, 16, 32, WindowHandle[1]);
	FrameHandle[4] = DerivationGraph(48, 16, 16, 32, WindowHandle[1]);
	FrameHandle[5] = DerivationGraph(0, 48, 16, 16, WindowHandle[1]);
	FrameHandle[6] = DerivationGraph(16, 48, 32, 16, WindowHandle[1]);
	FrameHandle[7] = DerivationGraph(48, 48, 16, 16, WindowHandle[1]);

	return true;
}

GAMETASK_CODE BattlePlayerTask::Update()
{
	return TASK_SUCCEEDED;
}

GAMETASK_CODE BattlePlayerTask::Draw()
{
	//”wŒi•`‰æ
	DrawRotaGraph(320, 240, 1.2, 0, BackGroundHandle, true);

	//ƒEƒBƒ“ƒhƒE•`‰æ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawExtendGraph(0, 0, 640, 112, WindowHandle[2], true);
	DrawExtendGraph(512, 352, 640, 480, WindowHandle[2], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawGraph(0, 0, FrameHandle[0], true);
	DrawGraph(0, 112 - 16, FrameHandle[5], true);
	DrawGraph(640 - 16, 0, FrameHandle[2], true);
	DrawGraph(640 - 16, 112 - 16, FrameHandle[7], true);
	DrawRotaGraph3(0, 16, 0, 0, 1.0, 2.5, 0, FrameHandle[3], true);
	DrawRotaGraph3(640 - 16, 16, 0, 0, 1.0, 2.5, 0, FrameHandle[4], true);
	for (int i = 0; i < 19; i++)
	{
		DrawGraph(32 * i + 16, 0, FrameHandle[1], true);
		DrawGraph(32 * i + 16, 96, FrameHandle[6], true);
	}

	DrawGraph(512, 352, FrameHandle[0], true);
	DrawGraph(512, 480 - 16, FrameHandle[5], true);
	DrawGraph(640 - 16, 352, FrameHandle[2], true);
	DrawGraph(640 - 16, 480 - 16, FrameHandle[7], true);
	DrawRotaGraph3(512, 368, 0, 0, 1.0, 3.0, 0, FrameHandle[3], true);
	DrawRotaGraph3(640 - 16, 368, 0, 0, 1.0, 3.0, 0, FrameHandle[4], true);
	DrawRotaGraph3(512 + 16, 352, 0, 0, 3.0, 1.0, 0, FrameHandle[1], true);
	DrawRotaGraph3(512 + 16, 480 - 16, 0, 0, 3.0, 1.0, 0, FrameHandle[6], true);

	SetFontSize(32);
	DrawString(260, 40, "ƒeƒXƒg", GetColor(255, 255, 255));

	DrawString(540, 380, "UŒ‚", GetColor(255, 255, 255));
	DrawString(540, 420, "“¹‹ï", GetColor(255, 255, 255));

	//Ž©ƒLƒƒƒ‰•`‰æ
	DrawRotaGraph(500, 240, 1.2, 0, CharaGraphHandle[0][0], true);

	//“GƒLƒƒƒ‰•`‰æ
	DrawRotaGraph(160, 240, 1.2, 0, CharaGraphHandle2[0][0], true, true);

	return TASK_SUCCEEDED;
}

bool BattlePlayerTask::Exit()
{
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 3; y++)
			DeleteGraph(CharaGraphHandle[x][y]);

	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 3; y++)
			DeleteGraph(CharaGraphHandle2[x][y]);

	for (int x = 0; x < 4; x++)
		DeleteGraph(WindowHandle[x]);

	DeleteGraph(BackGroundHandle);

	return true;
}