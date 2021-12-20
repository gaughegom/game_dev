#include "Brick.h"


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
