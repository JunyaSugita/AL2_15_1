#pragma once
#include "Struct.h"
class Player {
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//�����o�֐�
public:
	void PlayerMove(int gravityArrow, ISHIT& isHit);
	void DrawPlayer(float easingNum);
	//�����o�ϐ�
public:
	PLAYER player;
};