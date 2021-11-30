#include "Sprites.h"

CSprites* CSprites::__instance = nullptr;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprites::Add(int id, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, width, height, tex);
	this->sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return this->sprites[id];
}
