#include "EnemyEyelet.h"
#include "CharacterBase.h"
#include "BigDestroyEffect.h"
#include "Player.h"

constexpr auto AnimationDefaultId = "df";
constexpr auto DetectedPlayerRadius = 160.0f;

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
}

void CEnemyEyelet::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
