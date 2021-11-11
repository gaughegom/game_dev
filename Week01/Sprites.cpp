#include "Sprites.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

CSprites* CSprites::__instance = NULL;

CSprites* CSprites::Get_instance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y)
{
	CGame* game = CGame::Get_instance();
	game->Draw(x, y, this->texture, this->left, this->top, this->right, this->bottom);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	this->sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return this->sprites[id];
}

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::Get_instance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	this->frames.push_back(frame);
}

void CAnimation::Render(float x, float y)
{
	DWORD now = GetTickCount();
	if (this->currentFrame == -1)
	{
		this->currentFrame = 0;
		this->lastFrameTime = now;
	}
	else
	{
		DWORD t = this->frames[currentFrame]->Get_time();
		if (now - this->lastFrameTime > t)
		{
			this->currentFrame++;
			this->lastFrameTime = now;
			if (currentFrame == frames.size()) this->currentFrame = 0;
		}

	}

	this->frames[currentFrame]->Get_sprite()->Draw(x, y);
}

CAnimations* CAnimations::__instance = NULL;

CAnimations* CAnimations::Get_instance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	this->animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return this->animations[id];
}