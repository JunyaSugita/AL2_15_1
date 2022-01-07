#include "Title.h"
#include "math.h"
#include "Easing.h"

Title::Title() {
	title = {
		WIN_WIDTH / 2,
		200.0f
	};

	animeTimer = 0;
	animeArrow = 0;

	titleGraph = LoadGraph("resource/RGB_title.png");
	pressGraph = LoadGraph("resource/RGB_press.png");
}

Title::~Title() {}

void Title::TitleMove() {
	if (animeArrow == 0) {
		animeTimer++;
	}
	else {
		animeTimer--;
	}

	if (animeTimer == 50) {
		animeArrow = 1;
	}
	if (animeTimer == 0) {
		animeArrow = 0;
	}
}

void Title::SceneTrans(char* keys, int& isSceneChange) {
	if (keys[KEY_INPUT_SPACE] == 1) {
		isSceneChange = 1;
	}
}

void Title::DrawTitle(float easingNum) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 - (animeTimer * 2));
	DrawGraph(title.x - 150 + easingNum, title.y - 50 + (sin(-PI / 2 + PI / 50 * animeTimer) + 1) / 2 * 30, titleGraph, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Title::DrawPress(float easingNum) {
	DrawGraph(title.x - 150 + easingNum, title.y - 50 + 300 + (sin(-PI / 2 + PI / 50 * animeTimer) + 1) / 2 * 30, pressGraph, true);
}