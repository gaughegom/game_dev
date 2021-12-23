#include "EnemyBallot.h"
#include "Player.h"
#include "BigDestroyEffect.h"
#include "BulletBase.h"

#define	V_BOXSIZE			Vector2D(18, 18)

constexpr auto AnimationDefaultId = "default";
constexpr auto SpriteIdleId = "idle";
constexpr auto DetectedPlayerXAsix = 40.0f;
constexpr auto OwnSpeed = 0.07f;
constexpr auto DelayAttackTime = 5000;

CEnemyBallot::CEnemyBallot()
{
	this->AddAnimation(AnimationDefaultId, "aniEBallot");		// animation
	this->AddSprite(SpriteIdleId, "sprEBallot00");		// for idle state

	// hp, damage
	this->hp = 20;
	this->damage = 10;
	
	this->velocity.y = OwnSpeed;

	// collider
	auto collider = new CCollider2D(this, true, false, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyBallot::Update(DWORD dt)
{
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		return;
	}

	LPGAMEOBJECT player = CPlayer::GetInstance()->GetPlayer();
	auto now = GetTickCount64();
	if (abs(this->position.x - player->GetPosition().x) < DetectedPlayerXAsix
		&& now - this->prevAttackTime > DelayAttackTime
		&& this->isFlying == false
		&& this->position.y > player->GetPosition().y) {
		this->velocity.y = -(OwnSpeed + 0.01f);
		this->vTarget = player->GetPosition();
		this->isFlying = true;
		this->prevAttackTime = now;
	}

	if (this->isFlying) {
		if (abs(this->position.y - player->GetPosition().y) < 5.0f) {
			this->velocity.y = OwnSpeed;
			this->isFlying = false;
		}
	}
}

void CEnemyBallot::Render()
{
	auto color = this->GetRenderColor();
	auto player = CPlayer::GetInstance()->GetPlayer();
	if (abs(this->position.x - player->GetPosition().x) < DetectedPlayerXAsix) {
		this->animations.at(AnimationDefaultId)->Render(this->position, this->nx, color);
	}
	else {
		this->sprites.at(SpriteIdleId)->Draw(this->position, this->nx, color);
	}
}

void CEnemyBallot::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CBrick*>(other)) {
		this->isFlying = false;
		this->velocity.y = OwnSpeed;
	}
	else if (dynamic_cast<CCharaterBase*>(other)) {
		other->TakeDamage(this->damage);
		this->TakeDamage(other->GetDamage());

		this->isFlying = false;
		this->velocity.y = OwnSpeed;
	}
	else if (dynamic_cast<CBulletBase*>(other)) {
		this->TakeDamage(other->GetDamage());
		other->SetHp(0);
	}
}

void CEnemyBallot::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
