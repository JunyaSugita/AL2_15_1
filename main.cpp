#include "BackScleen.h"
#include "Player.h"
#include "Particle.h"
#include "Gravity.h"
#include "After.h"
#include "Scene.h"
#include "Title.h"
#include "Easing.h"
#include "Info.h"
#include "Reset.h"
#include "Bgm.h"

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
	//�V�[���Ǘ�
	Scene* scene = new Scene();

	//�w�i
	BackScleen* backScleen = new BackScleen();

	//bgm
	Bgm* bgm = new Bgm();

	//�^�C�g��
	Title* title = new Title();

	//�v���C���[
	Player* player = new Player();

	//gravity
	Gravity* gravity = new Gravity();

	//�c��
	After* after = new After();

	//�p�[�e�B�N��
	Particle* particle = new Particle();

	//�C�[�W���O
	Easing* easing = new Easing();

	//���Z�b�g
	Reset* reset = new Reset();

	//���̑�
	Info* info = new Info();

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

		//�w�i
		backScleen->BackColor();

		//�C�[�W���O
		easing->easeOutSine();

		//�V�[���Ǘ�
		scene->SceneChange(easing->frame);

		//bgm
		bgm->PlayBgm();

		switch (scene->scene) {
			case 0:
				title->TitleMove();
				title->SceneTrans(keys, scene->isSceneChange);
				break;
			case 1:
				//�����蔻��̃��Z�b�g
				particle->ResetHit();

				//�d�͂̕�������
				gravity->GravityOpe(keys);

				//���Z�b�g
				reset->ResetKey(keys, scene->isSceneChange);

				if (easing->frame == 50) {
					delete player;
					player = new Player();
					delete gravity;
					gravity = new Gravity();
					delete after;
					after = new After();
					delete particle;
					particle = new Particle();
				}

				//�C�[�W���O
				after->UpdatePlayer(player->player);

				//�v���C���[�̈ړ�
				player->PlayerMove(gravity->gravityArrow, particle->isHit);

				//�ǂ̃p�[�e�B�N��
				particle->HitParticle(player->player);

				//�p�[�e�B�N��
				particle->PlayerParticle(player->player);

				break;
		}
		// �`�揈��
		//�w�i
		backScleen->ShowBackColor();

		switch (scene->scene) {
			case 0:
				title->DrawTitle(easing->easingNum);
				title->DrawPress(easing->easingNum);
				break;
			case 1:
				//�������
				info->DrawInfo(easing->easingNum);
				//�c��
				after->DrawEasing(player->player, easing->easingNum);
				//�ǂ̃p�[�e�B�N��
				particle->DrawHitParticle(easing->easingNum);
				//�p�[�e�B�N��
				particle->DrawPlayerParticle(easing->easingNum);
				//�v���C���[
				player->DrawPlayer(easing->easingNum);
				//���Z�b�g
				reset->ShowReset(easing->easingNum);
				break;
		}
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
	delete scene;
	delete backScleen;
	delete player;
	delete gravity;
	delete particle;
	delete after;
	delete title;
	delete easing;
	delete info;
	delete reset;

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
