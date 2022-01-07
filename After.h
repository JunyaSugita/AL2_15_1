#pragma once
#include "Struct.h"
#include "Player.h"

class After {
public:
	//コンストラクタ
	After();
	//デストラクタ
	~After();

public:
	void UpdatePlayer(PLAYER player);
	void DrawEasing(PLAYER player, float easingNUM);
public:
	const int OLD_CONST = 50;
	OLD_PLAYER oldPlayer[50];

	int drawR;
	int drawG;
	int drawB;
};

