#pragma once
#ifndef _SPRITE_H
#define _SPRITE_H

#include "resources.h"
#include "Game.h"

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int width;
	int height;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 tex);

	void Draw(Vector2D position, int nx, int alpha);
};
typedef CSprite* LPSPRITE;

#endif // !_SPRITE_H
