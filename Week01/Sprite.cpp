#include "Sprite.h"

CSprite::CSprite(int id, int left, int top, int width, int height, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->texture = tex;
}

void CSprite::Draw(Vector2D position, int nx, D3DCOLOR color)
{
	CGame* game = CGame::GetInstance();
	game->Draw(
		position, 
		nx, 
		this->texture, 
		this->left,
		this->top, 
		this->left + this->width, 
		this->top + this->height,
		color);
}
