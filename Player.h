#pragma once
#include "Struct.h"
class Player {
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
	//メンバ関数
public:
	void PlayerMove(int gravityArrow, ISHIT& isHit);
	void DrawPlayer(float easingNum);
	//メンバ変数
public:
	PLAYER player;
};