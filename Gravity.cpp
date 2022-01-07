#include "Gravity.h"

Gravity::Gravity() {
	gravityArrow = 0;
}

Gravity::~Gravity() {}

void Gravity::GravityOpe(char* keys) {
	if (keys[KEY_INPUT_W] == 1 || keys[KEY_INPUT_UP] == 1) {
		gravityArrow = 1;
	}
	else if (keys[KEY_INPUT_D] == 1 || keys[KEY_INPUT_RIGHT] == 1) {
		gravityArrow = 2;
	}
	else if (keys[KEY_INPUT_S] == 1 || keys[KEY_INPUT_DOWN] == 1) {
		gravityArrow = 3;
	}
	else if (keys[KEY_INPUT_A] == 1 || keys[KEY_INPUT_LEFT] == 1) {
		gravityArrow = 4;
	}
}