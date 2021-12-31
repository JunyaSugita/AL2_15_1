#include "BackScleen.h"
#include "DxLib.h"

BackScleen::BackScleen() {
	back = {
		100,	//r
		1,		//isR
		0,		//g
		0,		//isG
		0,		//b
		0		//isB
	};
}

BackScleen::~BackScleen() {}

void BackScleen::BackColor() {
	if (back.isR == 1) {
		back.r++;
		if (back.r >= 300) {
			back.isR = 0;
			back.isG = 1;
		}
	}
	else if (back.r > 0) {
		back.r--;
	}

	if (back.isG == 1) {
		back.g++;
		if (back.g >= 300) {
			back.isG = 0;
			back.isB = 1;
		}
	}
	else if (back.g > 0) {
		back.g--;
	}

	if (back.isB == 1) {
		back.b++;
		if (back.b >= 300) {
			back.isB = 0;
			back.isR = 1;
		}
	}
	else if (back.b > 0) {
		back.b--;
	}
}

void BackScleen::ShowBackColor() {
	DrawBox(0, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(back.r / 2, back.g / 2, back.b / 2), true);
}