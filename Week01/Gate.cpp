#include "Gate.h"
#include "Boss.h"

CGate::CGate()
{
}

CGate::CGate(Vector2D boundingBox)
{
	this->colliders.clear();
	auto collider = new CCollider2D(this, false, true, VectorZero(), boundingBox);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

CGate::CGate(Vector2D boundingBox, int next) : CGate::CGate(boundingBox)
{
	this->nextScene = next;
}

void CGate::Update(DWORD dt)
{
	if (CGame::GetInstance()->GetCurrentSceneId() == 7 && CBoss::GetCloneBooses().size() != 0) {
		this->hp = 0;
	}
}

void CGate::Render()
{
}
