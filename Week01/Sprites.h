#pragma once
#ifndef _SPRITES_H
#define _SPRITES_H

#include "Sprite.h"
#include "Game.h"

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites* __instance;

	std::unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);

	static CSprites* GetInstance();
};


#endif // !_SPRITES_H
