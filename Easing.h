#pragma once
class Easing {
public:
	Easing();
	~Easing();

public:
	void easeOutSine();

public:
	float frame;
	const int CONST_FRAME = 50;
	const double PI = 3.14159265f;
	float easingNum;
};

