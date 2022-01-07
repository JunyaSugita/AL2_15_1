#include "Reset.h"

Reset::Reset() {
	isShowResetGraph = 0;

	ResetGraph = LoadGraph("resource/RGB_RESET.png");
}

Reset::~Reset() {}

void Reset::ResetKey(char* keys,int& isSceneChange) {
	if (keys[KEY_INPUT_R]) {
		isSceneChange = 1;
		isShowResetGraph = 1;
	}
}

void Reset::ShowReset(float easingNum) {
	if (isShowResetGraph == 1) {
		DrawGraph(-1000 + (easingNum), 0, ResetGraph, true);
	}
}