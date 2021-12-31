#include "time.h"
#include "BackScleen.h"

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
	Player player = {
		WIN_WIDTH / 2,		//x
		WIN_HEIGHT / 2,		//y
		16,					//r
		{					//speed
			0,					//x
			0					//y
		}
	};

	const int OLD_CONST = 50;
	OldPlayer oldPlayer[OLD_CONST];
	for (int i = 0; i < OLD_CONST; i++) {
		oldPlayer[i] = {
			player.x,
			player.y
		};
	}

	//gravity
	int gravityArrow = 0;

	//�C�[�W���O�`��
	int drawR = 0;
	int drawG = 1;
	int drawB = 2;

	//�ǂƓ������Ă��邩
	IsHit isHit = {
		0,		//UP
		0,		//DOWN
		0,		//RIGHT
		0		//LEFT
	};
	OldIsHit oldIsHit = {
		0,		//UP
		0,		//DOWN
		0,		//RIGHT
		0		//LEFT
	};

	//�~�̃p�[�e�B�N��
	const int CIRCLE_CONST = 100;
	Circle circle[CIRCLE_CONST];
	for (int i = 0; i < CIRCLE_CONST; i++) {
		circle[i] = {
			-100,	//x
			-100,	//y
			5,		//r
			0,		//show
			0,		//hitCount
		};
	}

	int isHitCount = 0;
	//�p�[�e�B�N��
	const int PAR_CONST = 1000;
	Par par[PAR_CONST];
	for (int i = 0; i < PAR_CONST; i++) {
		par[i] = {
			-100.0f,	//x
			-100.0f,	//y
			0,		//recoilX
			0,		//recoilY
			0,		//isShow
			0,		//time
			0		//color
		};
	}

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
		oldIsHit.up = isHit.up;
		oldIsHit.down = isHit.down;
		oldIsHit.right = isHit.right;
		oldIsHit.left = isHit.left;

		isHit = {
			0,		//UP
			0,		//DOWN
			0,		//RIGHT
			0		//LEFT
		};

		//�w�i
		backScleen->BackColor();

		//�d�͂̕�������
		if (keys[KEY_INPUT_W] == 1 || keys[KEY_INPUT_UP] == 1) {
			gravityArrow = 1;
		}
		else if (keys[KEY_INPUT_D] == 1 || keys[KEY_INPUT_RIGHT] == 1) {
			gravityArrow = 2;
		}
		else if (keys[KEY_INPUT_S] == 1 || keys[KEY_INPUT_DOWN] == 1) {
			gravityArrow = 3;
		}
		else if (keys[KEY_INPUT_A] == 1 || keys[KEY_INPUT_LEFT] == 1) {
			gravityArrow = 4;
		}

		//���Z�b�g
		if (keys[KEY_INPUT_R] == 1) {
			//������
			player = {
				WIN_WIDTH / 2,		//x
				WIN_HEIGHT / 2,		//y
				16,					//r
				{					//speed
					0,					//x
					0					//y
				}
			};
			for (int i = 0; i < OLD_CONST; i++) {
				oldPlayer[i] = {
					player.x,
					player.y
				};
			}

			gravityArrow = 0;
			drawR = 0;
			drawG = 1;
			drawB = 2;

			for (int i = 0; i < CIRCLE_CONST; i++) {
				circle[i] = {
					-100,
					-100,
					5,
					0,
					0
				};
			}

			isHitCount = 0;

			Back back = {
				100,		//r
				1,		//isR
				0,		//g
				0,		//isG
				0,		//b
				0		//isB
			};
		}

		//�C�[�W���O
		for (int i = OLD_CONST - 1; i > 0; i--) {
			oldPlayer[i].x = oldPlayer[i - 1].x;
			oldPlayer[i].y = oldPlayer[i - 1].y;
		}
		oldPlayer[0].x = player.x;
		oldPlayer[0].y = player.y;

		drawR++;
		drawG++;
		drawB++;
		if (drawR >= 3) {
			drawR = 0;
		}
		if (drawG >= 3) {
			drawG = 0;
		}
		if (drawB >= 3) {
			drawB = 0;
		}

		//�v���C���[�̈ړ�
		switch (gravityArrow) {
			case 1:
				if (player.speed.x > 0) {
					player.speed.x--;
				}
				else if (player.speed.x < 0) {
					player.speed.x++;
				}
				player.speed.y--;
				break;
			case 2:
				if (player.speed.y > 0) {
					player.speed.y--;
				}
				else if (player.speed.y < 0) {
					player.speed.y++;
				}
				player.speed.x++;
				break;
			case 3:
				if (player.speed.x > 0) {
					player.speed.x--;
				}
				else if (player.speed.x < 0) {
					player.speed.x++;
				}
				player.speed.y++;
				break;
			case 4:
				if (player.speed.y > 0) {
					player.speed.y--;
				}
				else if (player.speed.y < 0) {
					player.speed.y++;
				}
				player.speed.x--;
				break;
			default:
				break;
		}

		player.x += player.speed.x;
		player.y += player.speed.y;

		//�v���C���[����ʊO�ɍs���Ȃ��悤�ɂ���
		if (player.x <= 0 + player.r) {
			player.x = 0 + player.r;
			player.speed.x = 0;
			isHit.left = 1;
		}
		if (player.x >= WIN_WIDTH - player.r) {
			player.x = WIN_WIDTH - player.r;
			player.speed.x = 0;
			isHit.right = 1;
		}
		if (player.y <= 0 + player.r) {
			player.y = 0 + player.r;
			player.speed.y = 0;
			isHit.up = 1;
		}
		if (player.y >= WIN_HEIGHT - player.r) {
			player.y = WIN_HEIGHT - player.r;
			player.speed.y = 0;
			isHit.down = 1;
		}

		//�~�̃p�[�e�B�N��
		//��
		if (isHit.up == 1 && oldIsHit.up == 0) {
			isHitCount++;
			for (int i = 0; i < CIRCLE_CONST; i++) {
				if (circle[i].isShow == 0) {
					circle[i].x = player.x;
					circle[i].y = player.y - player.r;
					circle[i].isShow = 1;
					circle[i].hitCount = isHitCount;
					break;
				}
			}
		}
		//��
		if (isHit.down == 1 && oldIsHit.down == 0) {
			isHitCount++;
			for (int i = 0; i < CIRCLE_CONST; i++) {
				if (circle[i].isShow == 0) {
					circle[i].x = player.x;
					circle[i].y = player.y + player.r;
					circle[i].isShow = 1;
					circle[i].hitCount = isHitCount;
					break;
				}
			}
		}
		//�E
		if (isHit.right == 1 && oldIsHit.right == 0) {
			isHitCount++;
			for (int i = 0; i < CIRCLE_CONST; i++) {
				if (circle[i].isShow == 0) {
					circle[i].x = player.x + player.r;
					circle[i].y = player.y;
					circle[i].isShow = 1;
					circle[i].hitCount = isHitCount;
					break;
				}
			}
		}
		//��
		if (isHit.left == 1 && oldIsHit.left == 0) {
			isHitCount++;
			for (int i = 0; i < CIRCLE_CONST; i++) {
				if (circle[i].isShow == 0) {
					circle[i].x = player.x - player.r;
					circle[i].y = player.y;
					circle[i].isShow = 1;
					circle[i].hitCount = isHitCount;
					break;
				}
			}
		}

		for (int i = 0; i < CIRCLE_CONST; i++) {
			if (circle[i].isShow == 1) {
				circle[i].r += 5;
				if (circle[i].r >= 2000) {
					circle[i] = {
					-100,
					-100,
					5,
					0,
					0
					};
				}
			}
		}

		//�p�[�e�B�N��
		if (player.speed.x != 0 || player.speed.y != 0) {
			for (int j = 0; j < 5; j++) {
				for (int i = 0; i < PAR_CONST; i++) {
					if (par[i].isShow == 0) {
						par[i].isShow = 1;
						par[i].x = player.x;
						par[i].y = player.y;
						par[i].recoilX = (player.speed.x * -1) + rand() % 13 - 6;
						par[i].recoilY = (player.speed.y * -1) + rand() % 13 - 6;
						par[i].color = rand() % 3;
						break;
					}
				}
			}
		}

		for (int i = 0; i < PAR_CONST; i++) {
			if (par[i].isShow == 1) {
				par[i].x += par[i].recoilX / 5;
				par[i].y += par[i].recoilY / 5;
				par[i].time++;
				if (par[i].time >= 100) {
					par[i] = {
						-100.0f,	//x
						-100.0f,	//y
						0,		//recoilX
						0,		//recoilY
						0,		//isShow
						0,		//time
						0		//color
					};

				}
			}
		}

		// �`�揈��
		backScleen->ShowBackColor();

		//�C�[�W���O
		for (int i = 0; i < OLD_CONST; i++) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 150 - (i * 5));
			if (i % 3 == drawR) {
				DrawBox(oldPlayer[i].x - player.r, oldPlayer[i].y - player.r, oldPlayer[i].x + player.r, oldPlayer[i].y + player.r, GetColor(200, 0, 0), true);
			}
			if (i % 3 == drawG) {
				DrawBox(oldPlayer[i].x - player.r, oldPlayer[i].y - player.r, oldPlayer[i].x + player.r, oldPlayer[i].y + player.r, GetColor(0, 200, 0), true);
			}
			if (i % 3 == drawB) {
				DrawBox(oldPlayer[i].x - player.r, oldPlayer[i].y - player.r, oldPlayer[i].x + player.r, oldPlayer[i].y + player.r, GetColor(0, 0, 200), true);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		//�~�̃p�[�e�B�N��
		for (int i = 0; i < CIRCLE_CONST; i++) {
			if (circle[i].isShow == 1) {
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				if (circle[i].hitCount % 3 == 0) {
					for (int j = 0; j < 10; j++) {
						DrawCircle(circle[i].x, circle[i].y, circle[i].r - j, GetColor(255, 0, 0), false);
					}
				}
				else if (circle[i].hitCount % 3 == 1) {
					for (int j = 0; j < 10; j++) {
						DrawCircle(circle[i].x, circle[i].y, circle[i].r - j, GetColor(0, 255, 0), false);
					}
				}
				else if (circle[i].hitCount % 3 == 2) {
					for (int j = 0; j < 10; j++) {
						DrawCircle(circle[i].x, circle[i].y, circle[i].r - j, GetColor(0, 0, 255), false);
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}

		//�p�[�e�B�N��
		for (int i = 0; i < PAR_CONST; i++) {
			if (par[i].isShow == 1) {
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200 - par[i].time * 2);
				switch (par[i].color) {
					case 0:
						DrawCircle(par[i].x, par[i].y, 5, GetColor(255, 0, 0), true);
						break;
					case 1:
						DrawCircle(par[i].x, par[i].y, 5, GetColor(0, 255, 0), true);
						break;
					case 2:
						DrawCircle(par[i].x, par[i].y, 5, GetColor(0, 0, 255), true);
						break;
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}

		//�v���C���[
		DrawBox(player.x - player.r, player.y - player.r, player.x + player.r, player.y + player.r, GetColor(255, 255, 255), true);
		DrawBox(player.x - player.r, player.y - player.r, player.x + player.r, player.y + player.r, GetColor(255, 0, 0), false);

		//�O�g
		DrawBox(-50, -50, WIN_WIDTH + 50, 0, GetColor(255, 255, 255), true);
		DrawBox(-50, -50, 0, WIN_HEIGHT + 50, GetColor(255, 255, 255), true);
		DrawBox(-50, WIN_HEIGHT + 50, WIN_WIDTH + 50, WIN_HEIGHT, GetColor(255, 255, 255), true);
		DrawBox(WIN_WIDTH + 50, -50, WIN_WIDTH, WIN_HEIGHT + 50, GetColor(255, 255, 255), true);
		//�f�o�b�N
		DrawFormatString(0, 0, GetColor(255, 255, 255), "isHitCount:%d", isHitCount);


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

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
