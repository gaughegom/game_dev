#include "BulletBase.h"

CBulletBase::CBulletBase()
{
}

void CBulletBase::UpgradeLevel(const int& value)
{
	this->level = level;
	this->damage = this->damage * this->level;
}

void CBulletBase::Update(DWORD dt)
{
}

void CBulletBase::Render()
{
}

void CBulletBase::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
