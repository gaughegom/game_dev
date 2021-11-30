#include "GameObject.h"

//std::vector<LPANIMATION> CGameObject::animations;

CGameObject::CGameObject()
{
	this->position.x = this->position.y = 0;
	this->velocity.x = this->velocity.y = 0;
	this->nx = 1;
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

void CGameObject::AddAnimation(std::string key, int animationId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(animationId);
	this->animations.insert(std::make_pair(key, ani));
}

void CGameObject::PhysicalUpdate(std::vector<LPGAMEOBJECT>* coObjects)
{
	for (auto collider : this->colliders) {
		collider->PhysicalUpdate(coObjects);
	}
}

void CGameObject::OnCollision(CCollider2D* selfCollider, LPCOLLISIONEVENT collision)
{
}

void CGameObject::OnTrigger(CCollider2D* selfCollider, LPCOLLISIONEVENT collsion)
{
}

CGameObject::~CGameObject()
{
	this->animations.clear();
}