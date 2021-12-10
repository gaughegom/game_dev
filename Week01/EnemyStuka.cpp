#include "EnemyStuka.h"
#include "ControllerObject.h"
#include "SophiaBullet.h"

#define ANIMATION_DEFAULT_ID	"df"

CEnemyStuka::CEnemyStuka()
{
	this->AddAnimation(ANIMATION_DEFAULT_ID, "aniEStuka");
	this->hp = 10;
	this->damage = 10;

	this->active = false;

	//
	this->colliders.clear();
	auto collider = new CCollider2D(this, true, true, VectorZero(), V_STUKA_BOXSIZE);
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
	animations.at(ANIMATION_DEFAULT_ID)->Render(this->position, 1, DRAW_COLOR_DEFAULT);
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
	else if (dynamic_cast<CSophiaBullet*>(coEvent->object)) {
		this->TakeDamage(coEvent->object);
		auto bullet = (CSophiaBullet*)coEvent->object;
		bullet->OnDelete();
	}
}
