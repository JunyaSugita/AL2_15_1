#pragma once
#include "Struct.h"

class BackScleen{
public:
	//コンストラクタ
	BackScleen();
	//デストラクタ
	~BackScleen();
	
	//メンバ関数
public:
	void BackColor(Back &back);
	//メンバ変数
public:
	Back back;
};

