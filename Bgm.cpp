#include "Bgm.h"

Bgm::Bgm() {
	mainBgm = LoadSoundMem("sound/RGB_BGM.mp3");
	ChangeVolumeSoundMem(50, mainBgm);
}

Bgm::~Bgm() {}

void Bgm::PlayBgm() {
	if (CheckSoundMem(mainBgm) == 0) {
		PlaySoundMem(mainBgm, DX_PLAYTYPE_LOOP, true);
	}
}