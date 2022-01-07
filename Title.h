#pragma once
#include "Struct.h"

class Title {
public:
	Title();
	~Title();

public:
	void TitleMove();
	void SceneTrans(char* kays, int& SceneChange);
	void DrawTitle(float easingNum);
	void DrawPress(float easingNum);
public:
	TITLEPOS title;
	int animeTimer;
	int animeArrow;
	const float PI = 3.141592f;

	int titleGraph;
	int pressGraph;
};

