#include "Particle.h"

Particle::Particle() {
	for (int i = 0; i < CIRCLE_CONST; i++) {
		circle[i] = {
			-100,	//x
			-100,	//y
			5,		//r
			0,		//show
			0,		//hitCount
		};
	}

	for (int i = 0; i < PAR_CONST; i++) {
		par[i] = {
			-100.0f,	//x
			-100.0f,	//y
			0,		//recoilX
			0,		//recoilY
			0,		//isShow
			0,		//time
			0		//color
		};
	}

	isHit = {
		0,		//UP
		0,		//DOWN
		0,		//RIGHT
		0		//LEFT
	};
	oldIsHit = {
		0,		//UP
		0,		//DOWN
		0,		//RIGHT
		0		//LEFT
	};
	isHitCount = 0;

	piano = {
		LoadSoundMem("sound/pianoC.mp3"),
		LoadSoundMem("sound/pianoD.mp3"),
		LoadSoundMem("sound/pianoE.mp3"),
		LoadSoundMem("sound/pianoF.mp3"),
		LoadSoundMem("sound/pianoG.mp3"),
		LoadSoundMem("sound/pianoA.mp3"),
		LoadSoundMem("sound/pianoB.mp3"),
		LoadSoundMem("sound/pianoC+.mp3")
	};

	ChangeVolumeSoundMem(30, piano.c);
	ChangeVolumeSoundMem(30, piano.d);
	ChangeVolumeSoundMem(30, piano.e);
	ChangeVolumeSoundMem(30, piano.f);
	ChangeVolumeSoundMem(30, piano.g);
	ChangeVolumeSoundMem(30, piano.a);
	ChangeVolumeSoundMem(30, piano.b);
	ChangeVolumeSoundMem(30, piano.cc);

	//óêêî
	srand(time(NULL));
}

Particle::~Particle() {}

void Particle::PlayerParticle(PLAYER player) {
	if (player.speed.x != 0 || player.speed.y != 0) {
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < PAR_CONST; i++) {
				if (par[i].isShow == 0) {
					par[i].isShow = 1;
					par[i].x = player.x;
					par[i].y = player.y;
					par[i].recoilX = (player.speed.x * -1) + rand() % 13 - 6;
					par[i].recoilY = (player.speed.y * -1) + rand() % 13 - 6;
					par[i].color = rand() % 3;
					break;
				}
			}
		}
	}

	for (int i = 0; i < PAR_CONST; i++) {
		if (par[i].isShow == 1) {
			par[i].x += par[i].recoilX / 5;
			par[i].y += par[i].recoilY / 5;
			par[i].time++;
			if (par[i].time >= 100) {
				par[i] = {
					-100.0f,	//x
					-100.0f,	//y
					0,		//recoilX
					0,		//recoilY
					0,		//isShow
					0,		//time
					0		//color
				};

			}
		}
	}
}

void Particle::HitParticle(PLAYER player) {
	//è„
	if (isHit.up == 1 && oldIsHit.up == 0) {
		isHitCount++;
		for (int i = 0; i < CIRCLE_CONST; i++) {
			if (circle[i].isShow == 0) {
				circle[i].x = player.x;
				circle[i].y = player.y - player.r;
				circle[i].isShow = 1;
				circle[i].hitCount = isHitCount;
				switch (rand() % 8) {
					case 0:
						PlaySoundMem(piano.c, DX_PLAYTYPE_BACK, true);
						break;
					case 1:
						PlaySoundMem(piano.d, DX_PLAYTYPE_BACK, true);
						break;
					case 2:
						PlaySoundMem(piano.e, DX_PLAYTYPE_BACK, true);
						break;
					case 3:
						PlaySoundMem(piano.f, DX_PLAYTYPE_BACK, true);
						break;
					case 4:
						PlaySoundMem(piano.g, DX_PLAYTYPE_BACK, true);
						break;
					case 5:
						PlaySoundMem(piano.a, DX_PLAYTYPE_BACK, true);
						break;
					case 6:
						PlaySoundMem(piano.b, DX_PLAYTYPE_BACK, true);
						break;
					case 7:
						PlaySoundMem(piano.cc, DX_PLAYTYPE_BACK, true);
						break;
				}
				break;
			}
		}
	}
	//â∫
	if (isHit.down == 1 && oldIsHit.down == 0) {
		isHitCount++;
		for (int i = 0; i < CIRCLE_CONST; i++) {
			if (circle[i].isShow == 0) {
				circle[i].x = player.x;
				circle[i].y = player.y + player.r;
				circle[i].isShow = 1;
				circle[i].hitCount = isHitCount;
				switch (rand() % 8) {
					case 0:
						PlaySoundMem(piano.c, DX_PLAYTYPE_BACK, true);
						break;
					case 1:
						PlaySoundMem(piano.d, DX_PLAYTYPE_BACK, true);
						break;
					case 2:
						PlaySoundMem(piano.e, DX_PLAYTYPE_BACK, true);
						break;
					case 3:
						PlaySoundMem(piano.f, DX_PLAYTYPE_BACK, true);
						break;
					case 4:
						PlaySoundMem(piano.g, DX_PLAYTYPE_BACK, true);
						break;
					case 5:
						PlaySoundMem(piano.a, DX_PLAYTYPE_BACK, true);
						break;
					case 6:
						PlaySoundMem(piano.b, DX_PLAYTYPE_BACK, true);
						break;
					case 7:
						PlaySoundMem(piano.cc, DX_PLAYTYPE_BACK, true);
						break;
				}
				break;
			}
		}
	}
	//âE
	if (isHit.right == 1 && oldIsHit.right == 0) {
		isHitCount++;
		for (int i = 0; i < CIRCLE_CONST; i++) {
			if (circle[i].isShow == 0) {
				circle[i].x = player.x + player.r;
				circle[i].y = player.y;
				circle[i].isShow = 1;
				circle[i].hitCount = isHitCount;
				switch (rand() % 8) {
					case 0:
						PlaySoundMem(piano.c, DX_PLAYTYPE_BACK, true);
						break;
					case 1:
						PlaySoundMem(piano.d, DX_PLAYTYPE_BACK, true);
						break;
					case 2:
						PlaySoundMem(piano.e, DX_PLAYTYPE_BACK, true);
						break;
					case 3:
						PlaySoundMem(piano.f, DX_PLAYTYPE_BACK, true);
						break;
					case 4:
						PlaySoundMem(piano.g, DX_PLAYTYPE_BACK, true);
						break;
					case 5:
						PlaySoundMem(piano.a, DX_PLAYTYPE_BACK, true);
						break;
					case 6:
						PlaySoundMem(piano.b, DX_PLAYTYPE_BACK, true);
						break;
					case 7:
						PlaySoundMem(piano.cc, DX_PLAYTYPE_BACK, true);
						break;
				}
				break;
			}
		}
	}
	//ç∂
	if (isHit.left == 1 && oldIsHit.left == 0) {
		isHitCount++;
		for (int i = 0; i < CIRCLE_CONST; i++) {
			if (circle[i].isShow == 0) {
				circle[i].x = player.x - player.r;
				circle[i].y = player.y;
				circle[i].isShow = 1;
				circle[i].hitCount = isHitCount;
				switch (rand() % 8) {
					case 0:
						PlaySoundMem(piano.c, DX_PLAYTYPE_BACK, true);
						break;
					case 1:
						PlaySoundMem(piano.d, DX_PLAYTYPE_BACK, true);
						break;
					case 2:
						PlaySoundMem(piano.e, DX_PLAYTYPE_BACK, true);
						break;
					case 3:
						PlaySoundMem(piano.f, DX_PLAYTYPE_BACK, true);
						break;
					case 4:
						PlaySoundMem(piano.g, DX_PLAYTYPE_BACK, true);
						break;
					case 5:
						PlaySoundMem(piano.a, DX_PLAYTYPE_BACK, true);
						break;
					case 6:
						PlaySoundMem(piano.b, DX_PLAYTYPE_BACK, true);
						break;
					case 7:
						PlaySoundMem(piano.cc, DX_PLAYTYPE_BACK, true);
						break;
				}
				break;
			}
		}
	}

	for (int i = 0; i < CIRCLE_CONST; i++) {
		if (circle[i].isShow == 1) {
			circle[i].r += 5;
			if (circle[i].r >= 2000) {
				circle[i] = {
				-100,
				-100,
				5,
				0,
				0
				};
			}
		}
	}
}

void Particle::ResetHit() {
	oldIsHit.up = isHit.up;
	oldIsHit.down = isHit.down;
	oldIsHit.right = isHit.right;
	oldIsHit.left = isHit.left;

	isHit = {
		0,		//UP
		0,		//DOWN
		0,		//RIGHT
		0		//LEFT
	};
}

void Particle::DrawPlayerParticle(float easingNum) {
	for (int i = 0; i < PAR_CONST; i++) {
		if (par[i].isShow == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200 - par[i].time * 2);
			switch (par[i].color) {
				case 0:
					DrawCircle(par[i].x + easingNum, par[i].y, 5, GetColor(255, 0, 0), true);
					break;
				case 1:
					DrawCircle(par[i].x + easingNum, par[i].y, 5, GetColor(0, 255, 0), true);
					break;
				case 2:
					DrawCircle(par[i].x + easingNum, par[i].y, 5, GetColor(0, 0, 255), true);
					break;
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

void Particle::DrawHitParticle(float easingNum) {
	for (int i = 0; i < CIRCLE_CONST; i++) {
		if (circle[i].isShow == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			if (circle[i].hitCount % 3 == 0) {
				for (int j = 0; j < 10; j++) {
					DrawCircle(circle[i].x + easingNum, circle[i].y, circle[i].r - j, GetColor(255, 0, 0), false);
				}
			}
			else if (circle[i].hitCount % 3 == 1) {
				for (int j = 0; j < 10; j++) {
					DrawCircle(circle[i].x + easingNum, circle[i].y, circle[i].r - j, GetColor(0, 255, 0), false);
				}
			}
			else if (circle[i].hitCount % 3 == 2) {
				for (int j = 0; j < 10; j++) {
					DrawCircle(circle[i].x + easingNum, circle[i].y, circle[i].r - j, GetColor(0, 0, 255), false);
				}
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}