#pragma once
#include "Struct.h"
class Player{
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//�����o�֐�
public:
	void PlayerMove(int gravityArrow,ISHIT &isHit);
	void DrawPlayer();
	//�����o�ϐ�
public:
	PLAYER player;
};