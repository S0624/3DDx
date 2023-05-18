#include "DxLib.h"
#include"Player.h"
#include"Camera.h"
#include "game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // window���[�h�ݒ�
    ChangeWindowMode(Game::kWindowMode);

    // �E�C���h�E���ݒ�
    SetMainWindowText("�Q�[����");

    // ��ʃT�C�Y�̐ݒ�
    SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);
	SetWindowSizeChangeEnableFlag(true);//�E�B���h�E���[�h�̊g��k���i�T�C�Y�ύX�j
	SetAlwaysRunFlag(true);
    if (DxLib_Init() == -1)        // �c�w���C�u��������������
    {
        return -1;            // �G���[���N�����璼���ɏI��
    }
    // �_�u���o�b�t�@���[�h
    SetDrawScreen(DX_SCREEN_BACK);


	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(1600, 900, 16);

	// �J�����𐶐�.
	Camera* camera = new Camera();
	// �v���C���[�𐶐�.
	Player* player = new Player();

	
	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	LONGLONG frameTime = 0;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		frameTime = GetNowHiPerformanceCount();
		// �v���C���[����.
		player->Update();
		camera->Update(*player);

		// ��ʂ�����������
		ClearDrawScreen();		

// �f�o�b�O�`��
#if _DEBUG
		//(������)�O���b�h�̕\��
		for (float x = 100.0f; x <= 800.0f; x += 50.0f)
		{
			VECTOR start = VGet(x, 0.0f, -100.0f);		//���̎n�_
			VECTOR end = VGet(x, 0.0f, 1800.0f);		//���̏I�_
			DrawLine3D(start, end, 0x7fffd4);			//����
		}
		for (float z = -100.0f; z <= 1800.0f; z += 50.0f)
		{
			VECTOR start = VGet(100.0f, 0.0f, z);		//���̎n�_
			VECTOR end = VGet(800.0f, 0.0f, z);			//���̏I�_
			DrawLine3D(start, end, 0xdc143c);			//����
		}
		DrawString(0, 0, "Test",0x00ff00);

		//auto i = GetDrawCallCount();
		//DrawFormatString(800, 100, 0x0000ff, "%d", i);
#endif // kWindowMode

		// �`��
		player->Draw();

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		// �G��60fps�Œ�
		while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}

	}
    // ��n��
    delete(player);
    delete(camera);
    DxLib_End();                // �c�w���C�u�����g�p�̏I������

    return 0;                // �\�t�g�̏I��
}