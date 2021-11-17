#include "GameObject.h"

vector<LPANIMATION> CGameObject::animations;

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

void CGameObject::SetNewX(float x)
{
	this->position.x = x;
}

void CGameObject::SetNewY(float y)
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

void CGameObject::AddAnimation(int animationId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(animationId);
	animations.push_back(ani);
}

CGameObject::~CGameObject()
{
}