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

	bool wait = true;
	bool reverse = false;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(Vector2D position, int nx);

	void SetWait(bool value);
	void SetReverse(bool value);
	bool GetWait();
	bool GetReverse();
};
typedef CAnimation* LPANIMATION;

#endif // !_ANIMATION_H
