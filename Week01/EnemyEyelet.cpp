#include "EnemyEyelet.h"
#include "Sophia.h"
#include "SophiaBullet.h"
#include <math.h>

CEnemyEyelet::CEnemyEyelet()
{
	this->AddAnimation("default", 220); // eyelet animation id

	this->hp = 10;
	this->damage = 10;

	this->active = false;

	//
	this->colliders.clear();
	auto collider = new CCollider2D(this, true, true, VectorZero(), V_EYELET_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(colliders);
}

void CEnemyEyelet::Update(DWORD dt)
{
	if (PositionsDistance(CControllerObject::GetInstance()->GetPlayer()->GetPosition(), this->position) < ENEMY_ACTIVE_DISTANCE) {
		this->active = true;
	}

	if (this->active) {
		this->velocity.x = this->nx * ENEMY_VELOCITY_NORMAL;
		InSinWave(this, dt, 1.0f);
	}
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
	LPGAMEOBJECT player = CControllerObject::GetInstance()->GetPlayer();
	if ((dynamic_cast<CSophia*>(coEvent->object) || dynamic_cast<CJason*>(coEvent->object)) 
		&& player == coEvent->object) {
		LPGAMEOBJECT thisObject = dynamic_cast<LPGAMEOBJECT>(this);
		coEvent->object->TakeDamage(thisObject);
	}
	else if (dynamic_cast<CSophiaBullet*>(coEvent->object)) {
		this->TakeDamage(coEvent->object);
	}
}
