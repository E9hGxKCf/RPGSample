#include "DxLib.h"
#include "IScene.h"

class KeyChecker
{
private:
	char Buf[256];
	char StateBuf[256];

public:
	KeyChecker()
	{
		ZeroMemory(Buf, sizeof(char) * 256);
		ZeroMemory(StateBuf, sizeof(char) * 256);
	}

	void CheckKeyState()
	{
		GetHitKeyStateAll(StateBuf);

		for (int i = 0; i < 256; i++)
		{
			if (StateBuf[i] == 1)
				Buf[i]++;
			else
				Buf[i] = 0;
		}
	}

	bool GetKeyDown(int KeyCode)
	{
		return (Buf[KeyCode] == 1 ? true : false);
	}
};

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
	std::shared_ptr<IScene> ExecScene = CreateTitleScene();
	ExecScene->Init();

	//�Q�[�����[�v
	while (!ProcessMessage())
	{
		//��ʏ�����
		ClearDrawScreen();

		//�V�[�������s����
		if (!ExecScene->Exec())
		{
			ExecScene->Exit();

			//���̃V�[�����擾
			ExecScene = ExecScene->GetNextScene();
			ExecScene->Init();
		}

		//����ʏ���\��ʂɓ]��
		ScreenFlip();
	}

	//�V�[���̏I������
	ExecScene->Exit();

	//Dx���C�u�����̏I������
	DxLib_End();

	return 0;
}
