#pragma once
#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "AnimationFrame.h"
#include "Sprites.h"

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	std::vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(Vector2D position, int nx);
};
typedef CAnimation* LPANIMATION;

#endif // !_ANIMATION_H
