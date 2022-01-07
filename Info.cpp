#include "Info.h"
#include "Struct.h"

Info::Info() {}

Info::~Info() {}

void Info::DrawInfo(float easingNum) {
	DrawFormatString(0 + easingNum, 0, GetColor(255, 255, 255),"重力方向操作　W 　　　↑\n            ASD or ←↓→");
	DrawFormatString(0 + easingNum, 40, GetColor(255, 255, 255), "リセット　    R");
}