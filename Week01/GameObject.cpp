#include "GameObject.h"

//std::vector<LPANIMATION> CGameObject::animations;

CGameObject::CGameObject()
{
	this->position.x = this->position.y = 0;
	this->velocity.x = this->velocity.y = 0;
	this->nx = 1;
}

void CGameObject::Render()
{
}

Vector2D CGameObject::GetPosition()
{
	return this->position;
}

void CGameObject::SetX(float x)
{
	this->position.x = x;
}

void CGameObject::SetY(float y)
{
	this->position.y = y;
}

void CGameObject::SetNx(float newNX)
{
	this->nx = newNX;
}

float CGameObject::GetX()
{
	return this->position.x;
}

float CGameObject::GetY()
{
	return this->position.y;
}

int CGameObject::GetNx()
{
	return this->nx;
}

void CGameObject::AddAnimation(int key, int animationId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(animationId);
	this->animations.insert(std::make_pair(key, ani));
}

CGameObject::~CGameObject()
{
	this->animations.clear();
}