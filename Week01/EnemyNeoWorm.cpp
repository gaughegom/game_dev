#include "EnemyNeoWorm.h"
#include "Brick.h"
#include "Sophia.h"
#include "SophiaBullet.h"

#define V_BOXSIZE		Vector2D(18.0f, 10.0f)

constexpr auto AnimationDefaultId = "df";
constexpr auto LifeTime = 1500;

CEnemyNeoWorm::CEnemyNeoWorm()
{
	this->AddAnimation(AnimationDefaultId, "aniENeoworm");
	
	this->damage = 5;
	this->hp = 10;

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
	if (GetTickCount64() - this->bornTime > LifeTime) {
		this->hp = 0;
	}
}

void CEnemyNeoWorm::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->animations.at(AnimationDefaultId)->Render(this->position, -this->nx, color);
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
		LPGAMEOBJECT thisObj = (CGameObject*)this;
		coEvent->object->TakeDamage(this->damage);
		this->TakeDamage(coEvent->object->GetDamage());

		STriggerTag tag = STriggerTag(coEvent->object);
		coEvent->object->AddTriggerTag(this);
		this->AddTriggerTag(coEvent->object);
	}
	else if (dynamic_cast<CSophiaBullet*>(coEvent->object)) {
		this->TakeDamage(coEvent->object->GetDamage());
		CSophiaBullet* bullet = (CSophiaBullet*)coEvent->object;
		bullet->OnDelete();
	}
}

void CEnemyNeoWorm::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
