#include "EnemyNeoWorm.h"
#include "Brick.h"
#include "Sophia.h"
#include "SophiaBullet.h"

#define V_BOXSIZE		Vector2D(18.0f, 10.0f)
#define ANIMATION_ID	"df"
#define LIFETIME		1500

CEnemyNeoWorm::CEnemyNeoWorm()
{
	this->AddAnimation(ANIMATION_ID, "aniENeoworm");
	

	//
	this->colliders.clear();
	auto collider = new CCollider2D(this, true, false, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyNeoWorm::Update(DWORD dt)
{
	InGravityAffect(this, dt);
	if (this->ground == true) {
		this->velocity.x = this->nx * 0.05f;
	}
	if (GetTickCount64() - this->bornTime > LIFETIME) {
		this->hp = 0;
	}
}

void CEnemyNeoWorm::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->animations.at(ANIMATION_ID)->Render(this->position, -this->nx, color);
}

void CEnemyNeoWorm::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CBrick*>(coEvent->object) && this->ground == false) {
		this->ground = true;
	}
	else if (dynamic_cast<CEnemyNeoWorm*>(coEvent->object)) {
		this->hp = 0;
	}
	else if (dynamic_cast<CSophia*>(coEvent->object)) {
		STriggerTag tag = STriggerTag(coEvent->object);
		this->AddTriggerTag(coEvent->object);
		coEvent->object->AddTriggerTag(this);
	}
	else if (dynamic_cast<CSophiaBullet*>(coEvent->object)) {
		this->TakeDamage(coEvent->object);
		CSophiaBullet* bullet = (CSophiaBullet*)coEvent->object;
		bullet->OnDelete();
	}
}

void CEnemyNeoWorm::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
