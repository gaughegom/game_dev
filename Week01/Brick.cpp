#include "Brick.h"

#define BRICK_BOX_SIZE		Vector2D(16.0f, 16.0f)

// WARN: do not use this anymore
//CBrick::CBrick()
//{
//	auto collider = new CCollider2D;
//	collider->SetGameObject(this);
//	collider->SetOffset(VectorZero());
//	collider->SetBoxSize(BRICK_BOX_SIZE);
//	this->colliders.push_back(collider);
//}

CBrick::CBrick(Vector2D boundingBox)
{
	auto collider = new CCollider2D;
	collider->SetGameObject(this);
	collider->SetOffset(VectorZero());
	collider->SetBoxSize(boundingBox);
	this->colliders.push_back(collider);
}

void CBrick::Update(DWORD dt)
{
}

void CBrick::Render()
{
}
