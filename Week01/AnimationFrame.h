#pragma once
#ifndef _ANIMATION_FRAME_H
#define _ANIMATION_FRAME_H

#include "Sprite.h"

class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE _sprite, int _time);
	DWORD GetTime();
	LPSPRITE GetSprite();
};
typedef CAnimationFrame* LPANIMATION_FRAME;



#endif // !_ANIMATION_FRAME_H
