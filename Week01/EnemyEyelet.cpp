#include "EnemyEyelet.h"
#include "Sophia.h"
#include "SophiaBullet.h"
#include <math.h>

CEnemyEyelet::CEnemyEyelet()
{
	this->AddAnimation("default", 220); // eyelet animation id

	this->hp = 10;
	this->damage = 10;

	//
	this->colliders.clear();
	auto collider = new CCollider2D;
	collider->SetGameObject(this);
	collider->SetOffset(VectorZero());
	collider->SetBoxSize(Vector2D(18.0f, 15.0f));
	collider->SetDynamic(true);
	collider->SetTrigger(true);
	this->colliders.push_back(collider);
	this->SetColliders(colliders);
}

void CEnemyEyelet::Update(DWORD dt)
{
	this->velocity.x = this->nx * PLAYER_MOVING_SPEED;
	InSinWave(this, dt, 2.0f);
}

void CEnemyEyelet::Render()
{
	animations.at("default")->Render(this->position, 1, 255);
}

void CEnemyEyelet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CSophiaBullet*>(coEvent->object)) {
		this->TakeDamage(coEvent);
	}
}

void CEnemyEyelet::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CSophia*>(coEvent->object)) {
		DebugOut(L"collision with sophia\n");
	}
}
