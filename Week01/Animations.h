#pragma once
#ifndef _ANIMATIONS_H
#define _ANIMATIONS_H

#include "Animation.h"

class CAnimations
{
	static CAnimations* __instance;

	std::unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations* GetInstance();
};

#endif // !_ANIMATIONS_H
