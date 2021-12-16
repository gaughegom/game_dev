#include "EnemyGX-680S.h"
#include "Player.h"

#define ANIMATION_DEFAULT_ID		"df"
#define V_BOXSIZE					Vector2D(18.0f, 17.0f)
#define DETECTED_DISTANCE_PLAYER	80

#define OWN_VELOCITY				0.02f

CEnemyGX680S::CEnemyGX680S()
{
	this->AddAnimation(ANIMATION_DEFAULT_ID, "aniEGX680S");

	this->active = false;
	this->velocity = VectorZero();
	this->damage = 10;
	this->hp = 40;

	//
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyGX680S::Update(DWORD dt)
{
	LPGAMEOBJECT player = CPlayer::GetInstance()->GetPlayer();
	// detected player
	if (PositionsDistance(this->position, player->GetPosition()) < DETECTED_DISTANCE_PLAYER) {
		this->active = true;
	}

	// auto move to player
	if (this->active == true) {
		Vector2D vDistance = player->GetPosition() - this->position;
		if (vDistance.x != 0) vDistance.x = vDistance.x / abs(vDistance.x);
		if (vDistance.y != 0) vDistance.y = vDistance.y / abs(vDistance.y);

		this->velocity.x = vDistance.x * OWN_VELOCITY;
		this->velocity.y = vDistance.y * OWN_VELOCITY;
	}
}

void CEnemyGX680S::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	animations.at(ANIMATION_DEFAULT_ID)->Render(this->position, 1, color);
}

void CEnemyGX680S::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
