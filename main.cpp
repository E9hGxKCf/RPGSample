#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//��ʃ��[�h���E�B���h�E�ɕύX
	ChangeWindowMode(true);

	//�`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1)
		return -1;

	//�Q�[�����[�v
	while (!ProcessMessage())
	{
		//��ʏ�����
		ClearDrawScreen();

		//����ʏ���\��ʂɓ]��
		ScreenFlip();
	}

	//Dx���C�u�����̏I������
	DxLib_End();

	return 0;
}
