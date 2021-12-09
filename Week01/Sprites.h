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

	std::unordered_map<std::string, LPSPRITE> sprites;

public:
	void Add(std::string id, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(std::string id);

	static CSprites* GetInstance();
};


#endif // !_SPRITES_H
