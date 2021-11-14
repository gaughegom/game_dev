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

Vector2D CGameObject::Get_position()
{
	return this->position;
}

void CGameObject::Set_x(float x)
{
	this->position.x = x;
}

void CGameObject::Set_y(float y)
{
	this->position.y = y;
}

float CGameObject::Get_x()
{
	return this->position.x;
}

float CGameObject::Get_y()
{
	return this->position.y;
}

void CGameObject::Add_animation(int animationId)
{
	LPANIMATION ani = CAnimations::Get_instance()->Get(animationId);
	animations.push_back(ani);
}

CGameObject::~CGameObject()
{
}