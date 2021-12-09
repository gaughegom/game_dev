#include "EnemyStuka.h"
#include "ControllerObject.h"
#include "SophiaBullet.h"

CEnemyStuka::CEnemyStuka()
{
	this->AddAnimation("default", 210); // 210: stuka animation id
	this->hp = 10;
	this->damage = 10;

	this->active = false;

	//
	this->colliders.clear();
	auto collider = new CCollider2D;
	collider->SetGameObject(this);
	collider->SetOffset(VectorZero());
	collider->SetBoxSize(V_STUKA_BOXSIZE);
	collider->SetDynamic(true);
	collider->SetTrigger(true);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);

}

void CEnemyStuka::Update(DWORD dt)
{
	if (PositionsDistance(CControllerObject::GetInstance()->GetPlayer()->GetPosition(), this->position) < ENEMY_ACTIVE_DISTANCE) {
		this->active = true;
	}

	if (this->active) {
		this->velocity.x = this->nx * ENEMY_VELOCITY_NORMAL;
		InHorizontalMove(this, dt);
	}
}

void CEnemyStuka::Render()
{
	animations.at("default")->Render(this->position, 1, 255);
}

void CEnemyStuka::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CEnemyStuka::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CSophia*>(coEvent->object)) {
		LPGAMEOBJECT thisObject = dynamic_cast<LPGAMEOBJECT>(this);
		coEvent->object->TakeDamage(thisObject);
	}
	if (dynamic_cast<CSophiaBullet*>(coEvent->object)) {
		this->TakeDamage(coEvent->object);
	}
}
