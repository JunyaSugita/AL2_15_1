#include "Easing.h"
#include "math.h"

Easing::Easing() {
	frame = 0.0f;
	easingNum = 0.0f;
}

Easing::~Easing(){}

void Easing::easeOutSine() {
	easingNum = sin(((frame / CONST_FRAME) * PI) / 2) * 1000;
}