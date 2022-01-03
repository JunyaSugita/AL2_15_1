#pragma once
#include "Struct.h"
#include "Player.h"

class Easing{
public:
	//コンストラクタ
	Easing();
	//デストラクタ
	~Easing();

public:
	void UpdatePlayer(PLAYER player);
	void DrawEasing(PLAYER player);
public:
	const int OLD_CONST = 50;
	OLD_PLAYER oldPlayer[50];
	
	int drawR;
	int drawG;
	int drawB;
};

