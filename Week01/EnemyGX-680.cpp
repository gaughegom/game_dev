#include "EnemyGX-680.h"
#include "Player.h"
#include "BigDestroyEffect.h"
#include "ItemHealth.h"

#define V_BOXSIZE					Vector2D(18.0f, 17.0f)

constexpr auto DetectedPlayerRadius = 80;
constexpr auto AnimationDefaultId = "df";
constexpr auto OwnSpeed = 0.02f;
constexpr auto RateDropItemHealth = 0.3f;

CEnemyGX680::CEnemyGX680()
{
	this->AddAnimation(AnimationDefaultId, "aniEGX680");

	this->active = false;
	this->velocity = VectorZero();
	this->damage = 10;
	this->hp = 20;
	
	//
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyGX680::Update(DWORD dt)
{
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		
		float rate = (float)Random(1, 100) / 100;
		if (rate >= RateDropItemHealth) {
			CGame::GetInstance()->InitiateAndPushToQueue<CItemHealth>(this->position);
		}
		
		return;
	}

	LPGAMEOBJECT player = CPlayer::GetInstance()->GetPlayer();
	// detected player
	if (PositionsDistance(this->position, player->GetPosition()) < DetectedPlayerRadius) {
		this->active = true;
	}

	// auto move to player
	if (this->active == true) {
		Vector2D vDistance = player->GetPosition() - this->position - Vector2D(0, 12.0f);
		if (vDistance.x != 0) vDistance.x = vDistance.x / abs(vDistance.x);
		if (vDistance.y != 0) vDistance.y = vDistance.y / abs(vDistance.y);

		this->velocity.x = vDistance.x * OwnSpeed;
		this->velocity.y = vDistance.y * OwnSpeed;
	}
}

void CEnemyGX680::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	animations.at(AnimationDefaultId)->Render(this->position, 1, color);
}

void CEnemyGX680::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
