#include "DxLib.h"

#include "IScene.h"
#include "KeyDownChecker.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//��ʃ��[�h���E�B���h�E�ɕύX
	ChangeWindowMode(true);

	//�`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1)
		return -1;

	//�V�[�����擾�A����������
	std::shared_ptr<IScene> ExecScene = CreateBattleScene();// CreateMapScene();// CreateTitleScene();
	ExecScene->Init();

	//�L�[���̓`�F�b�N�N���X���쐬
	KeyDownChecker* Checker = KeyDownChecker::GetInstance();

/*
#include <memory>
#include "MapTask.h"
#include "PlayerTask.h"
#include "EnemyTask.h"

	std::shared_ptr<MapTask> task = std::make_shared<MapTask>();
	std::shared_ptr<PlayerTask> task2 = std::make_shared<PlayerTask>();
	std::shared_ptr<EnemyTask> task3 = std::make_shared<EnemyTask>();
	task->Init();
	task2->Init();
	task3->Init();*/

	//�Q�[�����[�v
	while (!ProcessMessage())
	{
		//��ʏ�����
		ClearDrawScreen();

		//�L�[����
		Checker->CheckKeyState();

	/*	task->Update();
		task2->Update();
		task3->Update();

		task->Draw();
		task2->Draw();
		task3->Draw();*/

		//�V�[�������s����
		if (!ExecScene->Exec())
		{
			ExecScene->Exit();

			//���̃V�[�����擾
			ExecScene = ExecScene->GetNextScene();
			ExecScene->Init();
		}/**/

		//����ʏ���\��ʂɓ]��
		ScreenFlip();
	}

/*	task->Exit();
	task2->Exit();
	task3->Exit();*/

	//�V�[���̏I������
	ExecScene->Exit();

	//Dx���C�u�����̏I������
	DxLib_End();

	return 0;
}
