#include "Sprites.h"

CSprites* CSprites::__instance = nullptr;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprites::Add(std::string id, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, width, height, tex);
	this->sprites.insert(std::make_pair(id, s));
}

LPSPRITE CSprites::Get(std::string id)
{
	return this->sprites.at(id);
}
