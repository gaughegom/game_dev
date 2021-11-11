#include "GameObject.h"

vector<LPANIMATION> CGameObject::animations;

CGameObject::CGameObject()
{
	this->x = this->y = 0;
	this->vx = this->vy = 0;
	this->nx = 1;
}

void CGameObject::Update(DWORD dt)
{
	this->x += this->vx * dt;
	this->y += this->vy * dt;
}

void CGameObject::Render()
{
}

void CGameObject::Add_animation(int aniId)
{
	LPANIMATION ani = CAnimations::Get_instance()->Get(aniId);
	animations.push_back(ani);
}

CGameObject::~CGameObject()
{
}