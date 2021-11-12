#include "GameObject.h"

vector<LPANIMATION> CGameObject::animations;

CGameObject::CGameObject()
{
	this->position.x = this->position.y = 0;
	this->velocity.x = this->velocity.y = 0;
	this->nx = 1;
}

void CGameObject::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CGameObject::Render()
{
}

void CGameObject::Set_x(float _x)
{
	this->position.x = _x;
}

void CGameObject::Set_y(float _y)
{
	this->position.y = _y;
}

void CGameObject::Add_animation(int _aniId)
{
	LPANIMATION ani = CAnimations::Get_instance()->Get(_aniId);
	animations.push_back(ani);
}

CGameObject::~CGameObject()
{
}