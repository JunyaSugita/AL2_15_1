#pragma once
#include "Struct.h"

class Particle{
public:
	//�R���X�g���N�^
	Particle();
	//�f�X�g���N�^
	~Particle();
public:
	void PlayerParticle(PLAYER player);
	void HitParticle(PLAYER player);
	void ResetHit();
	void DrawPlayerParticle(float easingNum);
	void DrawHitParticle(float easingNum);
public:
	const int CIRCLE_CONST = 100;
	CIRCLE circle[100];
	
	const int PAR_CONST = 1000;
	PAR par[1000];

	ISHIT isHit;
	OLD_ISHIT oldIsHit;
	int isHitCount;
};

