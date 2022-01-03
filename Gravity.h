#pragma once
#include "Struct.h"

class Gravity {
public:
	//コンストラクタ
	Gravity();
	//デストラクタ
	~Gravity();

public:
	void GravityOpe(char* keys);
public:
	int gravityArrow;
};

