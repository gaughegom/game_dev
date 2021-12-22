#include "LazerGuardBullet.h"
#include "SmallDestroyEffect.h"
#include "Player.h"

constexpr auto SpriteDefaultId = "df";
constexpr auto OwnSpeed = 0.07f;

CLazerGuardBullet::CLazerGuardBullet()
{
	this->AddSprite(SpriteDefaultId, "sprELazerBullet");

	this->damage = 10;

	//
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), Vector2D(16.0f, 33.0f));
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CLazerGuardBullet::Update(DWORD dt)
{
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CSmallDestroyEffect>(this->position);
		return;
	}

	if (this->vTarget == VectorZero()) {
		this->vTarget = CPlayer::GetInstance()->GetPlayer()->GetPosition() - this->position - Vector2D(0, 12.0f);
	}

	if (this->vTarget.x != 0) this->vTarget.x = this->vTarget.x / abs(this->vTarget.x);
	if (this->vTarget.y != 0) this->vTarget.y = this->vTarget.y / abs(this->vTarget.y);

	this->velocity.x = this->vTarget.x * OwnSpeed;
	this->velocity.y = this->vTarget.y * OwnSpeed;
}

void CLazerGuardBullet::Render()
{
	this->sprites.at(SpriteDefaultId)->Draw(this->position, this->nx, this->GetRenderColor());
}

void CLazerGuardBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CBrick*>(other)) {
		this->hp = 0;
	}
	else if (dynamic_cast<CEnemyBase*>(other) || dynamic_cast<CLazerGuardBullet*>(other)) {
		STriggerTag tag = STriggerTag(other);
		other->AddTriggerTag(this);
		this->AddTriggerTag(other);
	}
	else if (dynamic_cast<CCharaterBase*>(other)) {
		other->TakeDamage(this->damage);
		this->hp = 0;
	}
	else if (dynamic_cast<CBulletBase*>(other)) {
		this->hp = 0;
	}
}
