#pragma once
#ifndef _SPRITE_H
#define _SPRITE_H

#include "resources.h"
#include "Game.h"

class CSprite
{
	std::string id;				// Sprite ID in the sprite database

	int left;
	int top;
	int width;
	int height;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(std::string id, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 tex);

	void Draw(Vector2D position, int nx, D3DCOLOR color, int layer = DrawLayer01, float rotate = 0.0f);
};
typedef CSprite* LPSPRITE;

#endif // !_SPRITE_H
