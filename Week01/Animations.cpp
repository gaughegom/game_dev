#include "Animations.h"

CAnimations* CAnimations::__instance = nullptr;

CAnimations* CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(std::string id, LPANIMATION ani)
{
	this->animations.insert(std::make_pair(id, ani));
}

LPANIMATION CAnimations::Get(std::string id)
{
	return this->animations.at(id);
}

void CAnimations::Clear()
{
	for (auto x : this->animations) {
		LPANIMATION ani = x.second;
		delete ani;
	}
	this->animations.clear();
}
