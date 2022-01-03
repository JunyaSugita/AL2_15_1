#include "Easing.h"

Easing::Easing() {
	for (int i = 0; i < OLD_CONST; i++) {
		oldPlayer[i] = {
			-100,
			-100
		};
	}
	drawR = 0;
	drawG = 1;
	drawB = 2;
}

Easing::~Easing(){}

void Easing::UpdatePlayer(PLAYER player) {
	for (int i = OLD_CONST - 1; i > 0; i--) {
		oldPlayer[i].x = oldPlayer[i - 1].x;
		oldPlayer[i].y = oldPlayer[i - 1].y;
	}
	oldPlayer[0].x = player.x;
	oldPlayer[0].y = player.y;

	drawR++;
	drawG++;
	drawB++;
	if (drawR >= 3) {
		drawR = 0;
	}
	if (drawG >= 3) {
		drawG = 0;
	}
	if (drawB >= 3) {
		drawB = 0;
	}
}

void Easing::DrawEasing(PLAYER player) {
	for (int i = 0; i < OLD_CONST; i++) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, 150 - (i * 5));
		if (i % 3 == drawR) {
			DrawBox(oldPlayer[i].x - player.r, oldPlayer[i].y - player.r, oldPlayer[i].x + player.r, oldPlayer[i].y + player.r, GetColor(200, 0, 0), true);
		}
		if (i % 3 == drawG) {
			DrawBox(oldPlayer[i].x - player.r, oldPlayer[i].y - player.r, oldPlayer[i].x + player.r, oldPlayer[i].y + player.r, GetColor(0, 200, 0), true);
		}
		if (i % 3 == drawB) {
			DrawBox(oldPlayer[i].x - player.r, oldPlayer[i].y - player.r, oldPlayer[i].x + player.r, oldPlayer[i].y + player.r, GetColor(0, 0, 200), true);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}