#include "GameObject.h"

vector<LPANIMATION> CGameObject::animations;

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
}

void CGameObject::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
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