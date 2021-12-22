#include "EnemyEyelet.h"
#include "CharacterBase.h"
#include "BigDestroyEffect.h"
#include "Player.h"
#include "ItemHealth.h"

constexpr auto AnimationDefaultId = "df";
constexpr auto DetectedPlayerRadius = 70.0f;
constexpr auto RateDropItemHeath = 0.6f;

CEnemyEyelet::CEnemyEyelet()
{
	this->AddAnimation(AnimationDefaultId, "aniEEyelet");

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
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		
		float rate = (float)Random(1, 100) / 100;
		if (rate <= RateDropItemHeath) {
			CGame::GetInstance()->InitiateAndPushToQueue<CItemHealth>(this->position);
		}
		
		return;
	}

	this->ActiveByRadiusDistance(DetectedPlayerRadius);

	if (this->active) {
		this->velocity.x = (float)this->nx * EnemyNormalVelocity;
		InSinWaveXAsix(this, dt, 0.2f, 1.0f);
	}
}

void CEnemyEyelet::Render()
{
	auto color = this->GetRenderColor();
	animations.at(AnimationDefaultId)->Render(this->position, this->nx, color);
}

void CEnemyEyelet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CSophia*>(other)) {
		other->TakeDamage(this->damage);
		this->TakeDamage(other->GetDamage());

		STriggerTag tag = STriggerTag(other);
		other->AddTriggerTag(this);
		this->AddTriggerTag(other);
	}
}

void CEnemyEyelet::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
