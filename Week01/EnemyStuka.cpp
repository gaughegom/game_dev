#include "EnemyStuka.h"
#include "Player.h"
#include "BigDestroyEffect.h"

constexpr auto AnimationDefaultId = "df";
constexpr auto DetectedPlayerRadius = 130.0f;

CEnemyStuka::CEnemyStuka()
{
	this->AddAnimation(AnimationDefaultId, "aniEStuka");
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
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		return;
	}

	this->ActiveByRadiusDistance(DetectedPlayerRadius);

	if (this->active) {
		this->velocity.x = this->nx * EnemyNormalVelocity;
		InHorizontalMove(this, dt);
	}
}

void CEnemyStuka::Render()
{
	animations.at(AnimationDefaultId)->Render(this->position, 1, DrawArgbColorDefault());
}

void CEnemyStuka::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CEnemyStuka::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CSophia*>(coEvent->object)) {
		coEvent->object->TakeDamage(this->damage);
		this->TakeDamage(coEvent->object->GetDamage());
	}
}
