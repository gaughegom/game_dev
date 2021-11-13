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
	//Move_rectilinear(this->position, this->velocity, dt);
}

void CGameObject::Render()
{
}

void CGameObject::Set_x(float x)
{
	this->position.x = x;
}

void CGameObject::Set_y(float y)
{
	this->position.y = y;
}

void CGameObject::Add_animation(int animationId)
{
	LPANIMATION ani = CAnimations::Get_instance()->Get(animationId);
	animations.push_back(ani);
}

CGameObject::~CGameObject()
{
}