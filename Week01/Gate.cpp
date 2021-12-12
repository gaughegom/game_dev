#include "Gate.h"

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
}

void CGate::Render()
{
}
