#include "EnemyDrap.h"
#include "BigDestroyEffect.h"
#include "Player.h"
#include "BulletBase.h"

constexpr auto AnimationDefaultId = "df";
constexpr auto OwnSpeed = 0.13f;
constexpr auto DetectedPlayeyYAxis = 10.0f;

CEnemyDrap::CEnemyDrap()
{
	this->AddAnimation(AnimationDefaultId, "aniEDrap"); 

	this->hp = 20;
	this->damage = 10;


	//
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), Vector2D(17.0f, 17.0f));
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyDrap::Update(DWORD dt)
{
	if (this->IsLive() == false) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		return;
	}

	if (abs(this->position.y - CPlayer::GetInstance()->GetPlayer()->GetPosition().y) < DetectedPlayeyYAxis) {
		this->velocity.x = this->nx * OwnSpeed;
	}
}

void CEnemyDrap::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	LPANIMATION animation = this->animations.at(AnimationDefaultId);

	if (this->velocity.x == 0) {
		animation->SetWait(true);
	}
	else {
		animation->SetWait(false);
	}

	animation->Render(this->position, this->nx, color);

}

void CEnemyDrap::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CBrick*>(other)) {
		this->velocity = VectorZero();
		this->nx = -this->nx;
	}
	else if (dynamic_cast<CCharaterBase*>(other)) {
		if (dynamic_cast<CSophia*>(other)) {
			other->TakeDamage(this->damage);
			this->TakeDamage(other->GetDamage());

			STriggerTag tag = STriggerTag(other);
			other->AddTriggerTag(this);
			this->AddTriggerTag(other);
		}
	}
	else if (dynamic_cast<CBulletBase*>(other)) {
		this->TakeDamage(other->GetDamage());
		other->SetHp(0);
	}
}
