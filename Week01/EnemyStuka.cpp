#include "EnemyStuka.h"
#include "Player.h"
#include "BigDestroyEffect.h"
#include "ItemPower.h"

constexpr auto Speed = 0.08f;
constexpr auto AnimationDefaultId = "df";
constexpr auto DetectedPlayerRadius = 130.0f;
constexpr auto MaxStepMove = 60;
constexpr auto RateDropItemPower = 0.2;

CEnemyStuka::CEnemyStuka()
{
	this->AddAnimation(AnimationDefaultId, "aniEStuka");
	this->hp = 10;
	this->damage = 10;

	this->active = false;

	//
	this->colliders.clear();
	auto collider = new CCollider2D(this, true, false, VectorZero(), V_STUKA_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);

}

void CEnemyStuka::Update(DWORD dt)
{
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		
		float rate = (float)Random(1, 100) / 100;
		if (rate <= RateDropItemPower) {
			CGame::GetInstance()->InitiateAndPushToQueue<CItemPower>(this->position);
		}
		
		return;
	}

	this->ActiveByRadiusDistance(DetectedPlayerRadius);

	if (this->active) {
		if (this->stepMove > MaxStepMove) {
			this->nx = -this->nx;
			this->stepMove = 0;
		}
		else {
			this->stepMove++;
		}
		this->velocity.x = this->nx * Speed;
	}
}

void CEnemyStuka::Render()
{
	animations.at(AnimationDefaultId)->Render(this->position, 1, DrawArgbColorDefault());
}

void CEnemyStuka::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CSophia*>(other)) {
		other->TakeDamage(this->damage);
		this->TakeDamage(other->GetDamage());

		STriggerTag tag = STriggerTag(other);
		other->AddTriggerTag(this);
		this->AddTriggerTag(other);
	}
	else if (dynamic_cast<CEnemyStuka*>(other)) {
		STriggerTag tag = STriggerTag(other);
		other->AddTriggerTag(this);
		this->AddTriggerTag(other);
	}
	else if (dynamic_cast<CBrick*>(other)) {
		this->nx = -this->nx;
		this->stepMove = 0;
	}
}

void CEnemyStuka::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
