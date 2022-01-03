#pragma once
#include "Global.h"

//�v���C���[�̒�`
typedef struct {
	int x;
	int y;
}SPEED;

typedef struct {
	int x;
	int y;
	int r;
	SPEED speed;
}PLAYER;

typedef struct {
	int x;
	int y;
}OLD_PLAYER;

//�����蔻��̒�`
typedef struct {
	int up;
	int down;
	int right;
	int left;
}ISHIT;

typedef struct {
	int up;
	int down;
	int right;
	int left;
}OLD_ISHIT;

//�~�̃p�[�e�B�N��
typedef struct {
	int x;
	int y;
	int r;
	int isShow;
	int hitCount;
}CIRCLE;

//�w�i�`��
typedef struct {
	int r;
	int isR;
	int g;
	int isG;
	int b;
	int isB;
}BACK;

//�p�[�e�B�N��
typedef struct {
	float x;
	float y;
	float recoilX;
	float recoilY;
	int isShow;
	int time;
	int color;
}PAR;