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

	bool wait = false;
	bool reverse = false;
	bool loop = true;
	bool finish = false;

public:
	CAnimation();
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(std::string spriteId, DWORD time = 0);
	void Render(Vector2D position, int nx, D3DCOLOR color, int layer = DrawLayer01, float rotate = 0.0f);

	void SetWait(bool value);
	bool IsWait();

	void SetReverse(bool value);
	bool IsReverse();

	void SetLoop(bool value) { this->loop = value; }
	bool IsLoop() { return this->loop; }

	void SetFinish(bool value) { this->finish = value; }
	bool IsFinish() { return this->finish; }

};
typedef CAnimation* LPANIMATION;

#endif // !_ANIMATION_H
