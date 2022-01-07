#pragma once
#include "Struct.h"

class Reset {
public:
	Reset();
	~Reset();

public:
	void ResetKey(char* keys, int& isSceneChange);
	void ShowReset(float easingNum);
public:
	int isShowResetGraph;

	int ResetGraph;
};

