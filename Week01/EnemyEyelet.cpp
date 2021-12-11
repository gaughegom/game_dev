#include "EnemyEyelet.h"
#include "Sophia.h"
#include "SophiaBullet.h"


#define ANIMATION_DEFAULT_ID	"df"

CEnemyEyelet::CEnemyEyelet()
{
	this->AddAnimation(ANIMATION_DEFAULT_ID, "aniEEyelet");

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
	this->ScheduleActiveByDistance();

	if (this->active) {
		this->velocity.x = this->nx * ENEMY_VELOCITY_NORMAL;
		InSinWave(this, dt, 1.0f);
	}
}

void CEnemyEyelet::Render()
{
	auto color = this->GetRenderColor();
	animations.at(ANIMATION_DEFAULT_ID)->Render(this->position, 1, color);
}

void CEnemyEyelet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	
}

void CEnemyEyelet::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT player = CPlayer::GetInstance()->GetPlayer();
	if ((dynamic_cast<CSophia*>(coEvent->object) || dynamic_cast<CJason*>(coEvent->object)) 
		&& player == coEvent->object) {
		LPGAMEOBJECT thisObject = dynamic_cast<LPGAMEOBJECT>(this);
		coEvent->object->TakeDamage(thisObject);
	}
	else if (dynamic_cast<CSophiaBullet*>(coEvent->object)) {
		this->TakeDamage(coEvent->object);
		auto bullet = (CSophiaBullet*)coEvent->object;
		bullet->OnDelete();
	}
}
