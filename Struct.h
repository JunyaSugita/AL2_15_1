#pragma once

//�v���C���[�̒�`
typedef struct {
	int x;
	int y;
}Speed;

typedef struct {
	int x;
	int y;
	int r;
	Speed speed;
}Player;

typedef struct {
	int x;
	int y;
}OldPlayer;

//�����蔻��̒�`
typedef struct {
	int up;
	int down;
	int right;
	int left;
}IsHit;

typedef struct {
	int up;
	int down;
	int right;
	int left;
}OldIsHit;

//�~�̃p�[�e�B�N��
typedef struct {
	int x;
	int y;
	int r;
	int isShow;
	int hitCount;
}Circle;

//�w�i�`��
typedef struct {
	int r;
	int isR;
	int g;
	int isG;
	int b;
	int isB;
}Back;

//�p�[�e�B�N��
typedef struct {
	float x;
	float y;
	float recoilX;
	float recoilY;
	int isShow;
	int time;
	int color;
}Par;