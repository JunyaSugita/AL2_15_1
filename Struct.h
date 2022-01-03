#pragma once
#include "Global.h"

//プレイヤーの定義
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

//当たり判定の定義
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

//円のパーティクル
typedef struct {
	int x;
	int y;
	int r;
	int isShow;
	int hitCount;
}CIRCLE;

//背景描画
typedef struct {
	int r;
	int isR;
	int g;
	int isG;
	int b;
	int isB;
}BACK;

//パーティクル
typedef struct {
	float x;
	float y;
	float recoilX;
	float recoilY;
	int isShow;
	int time;
	int color;
}PAR;