#include "Scene.h"

Scene::Scene() {
	scene = 0;
	isSceneChange = 0;
}

Scene::~Scene() {}

void Scene::SceneChange(float& frame) {
	if (isSceneChange == 1) {
		if (frame >= 50) {
			scene = 1;
			isSceneChange = 0;
		}
		else {
			frame++;
		}
	}
	else if (frame > 0) {
		frame--;
	}
}