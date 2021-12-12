#include "Brick.h"

#define BRICK_BOX_SIZE		Vector2D(16.0f, 16.0f)

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
