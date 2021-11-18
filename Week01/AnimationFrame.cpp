#include "AnimationFrame.h"

CAnimationFrame::CAnimationFrame(LPSPRITE _sprite, int _time)
{
	this->sprite = _sprite;
	this->time = _time;
}

DWORD CAnimationFrame::GetTime()
{
	return this->time;
}

LPSPRITE CAnimationFrame::GetSprite() {
	return this->sprite;
}
