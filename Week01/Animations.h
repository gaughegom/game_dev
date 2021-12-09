#pragma once
#ifndef _ANIMATIONS_H
#define _ANIMATIONS_H

#include "Animation.h"

class CAnimations
{
	static CAnimations* __instance;

	std::unordered_map<std::string, LPANIMATION> animations;

public:
	void Add(std::string id, LPANIMATION ani);
	LPANIMATION Get(std::string id);

	static CAnimations* GetInstance();
};

#endif // !_ANIMATIONS_H
