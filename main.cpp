#include "time.h"
#include "BackScleen.h"
#include "Player.h"
#include "Particle.h"
#include "Gravity.h"
#include "Easing.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0, 0, 0);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	//�w�i
	BackScleen* backScleen = new BackScleen();

	//�v���C���[
	Player* player = new Player();

	//gravity
	Gravity* gravity = new Gravity();

	//�C�[�W���O
	Easing* easing = new Easing();

	//�p�[�e�B�N��
	Particle* particle = new Particle;

	//����
	srand(time(NULL));

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		//�z��Ȃ̂�oldkey - keys;�̂悤�ɂł��Ȃ��B�v�f���P���R�s�[

		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

		//�����蔻��̃��Z�b�g
		particle->ResetHit();

		//�w�i
		backScleen->BackColor();

		//�d�͂̕�������
		gravity->GravityOpe(keys);

		//���Z�b�g
		if (keys[KEY_INPUT_R] == 1) {
			
		}

		//�C�[�W���O
		easing->UpdatePlayer(player->player);

		//�v���C���[�̈ړ�
		player->PlayerMove(gravity->gravityArrow,particle->isHit);

		//�ǂ̃p�[�e�B�N��
		particle->HitParticle(player->player);

		//�p�[�e�B�N��
		particle->PlayerParticle(player->player);

		// �`�揈��
		backScleen->ShowBackColor();

		//�C�[�W���O
		easing->DrawEasing(player->player);
		//�ǂ̃p�[�e�B�N��
		particle->DrawHitParticle();

		//�p�[�e�B�N��
		particle->DrawPlayerParticle();
		//�v���C���[
		player->DrawPlayer();

		//�O�g
		DrawBox(-50, -50, WIN_WIDTH + 50, 0, GetColor(255, 255, 255), true);
		DrawBox(-50, -50, 0, WIN_HEIGHT + 50, GetColor(255, 255, 255), true);
		DrawBox(-50, WIN_HEIGHT + 50, WIN_WIDTH + 50, WIN_HEIGHT, GetColor(255, 255, 255), true);
		DrawBox(WIN_WIDTH + 50, -50, WIN_WIDTH, WIN_HEIGHT + 50, GetColor(255, 255, 255), true);

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	//�f�X�g���N�^
	delete backScleen;
	delete player;
	delete gravity;
	delete particle;
	delete easing;

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
