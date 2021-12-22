#include "Brick.h"
#include "BulletBase.h"
#include "EnemyStuka.h"

CBrick::CBrick(Vector2D boundingBox)
{
	auto collider = new CCollider2D(this, false, false, VectorZero(), boundingBox);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CBrick::Update(DWORD dt)
{
}

void CBrick::Render()
{
}

void CBrick::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CBulletBase*>(other)) {
		other->SetHp(0);
	}
}

void CBrick::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
