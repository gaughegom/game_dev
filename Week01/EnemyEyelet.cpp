#include "EnemyEyelet.h"
#include "Sophia.h"

CEnemyEyelet::CEnemyEyelet()
{
	this->AddAnimation("default", 220); // eyelet animation id

	//
	this->colliders.clear();
	auto collider = new CCollider2D;
	collider->SetGameObject(this);
	collider->SetOffset(VectorZero());
	collider->SetBoxSize(Vector2D(18.0f, 15.0f));
	collider->SetDynamic(true);
	this->colliders.push_back(collider);
	this->SetColliders(colliders);
}

void CEnemyEyelet::Update(DWORD dt)
{

}

void CEnemyEyelet::Render()
{
	animations.at("default")->Render(this->position, 1, 255);
}

void CEnemyEyelet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	
}

void CEnemyEyelet::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

CEnemyEyelet::~CEnemyEyelet()
{
}
