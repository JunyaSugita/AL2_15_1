#pragma once

//プレイヤーの定義
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

//当たり判定の定義
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

//円のパーティクル
typedef struct {
	int x;
	int y;
	int r;
	int isShow;
	int hitCount;
}Circle;

//背景描画
typedef struct {
	int r;
	int isR;
	int g;
	int isG;
	int b;
	int isB;
}Back;

//パーティクル
typedef struct {
	float x;
	float y;
	float recoilX;
	float recoilY;
	int isShow;
	int time;
	int color;
}Par;