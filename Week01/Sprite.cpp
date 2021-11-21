#include "Sprite.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

void CSprite::Draw(Vector2D position, int nx)
{
	CGame* game = CGame::GetInstance();
	game->Draw(position, nx, this->texture, this->left, this->top, this->right, this->bottom);
}
