#pragma once
#include "Struct.h"

class Scene {
public:
	Scene();
	~Scene();

public:
	void SceneChange(float& frame);

public:
	int scene;
	int isSceneChange;
};

