#include "EnemyEyelet.h"
#include "Sophia.h"

#define ANIMATION_DEFAULT_ID	"df"
#define DETACTED_PLAYER_DISTANCE	160.0f

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
	this->ScheduleActiveByDistance(DETACTED_PLAYER_DISTANCE);

	if (this->active) {
		this->velocity.x = this->nx * ENEMY_VELOCITY_NORMAL;
		InSinWaveXAsix(this, dt, 1.0f);
	}
}

void CEnemyEyelet::Render()
{
	auto color = this->GetRenderColor();
	animations.at(ANIMATION_DEFAULT_ID)->Render(this->position, this->nx, color);
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
		this->TakeDamage(coEvent->object);
	}
}
