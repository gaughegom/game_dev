#include "Animations.h"

CAnimations* CAnimations::__instance = nullptr;

CAnimations* CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	this->animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return this->animations[id];
}