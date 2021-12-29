#include "EnemyStuka.h"
#include "Player.h"
#include "BigDestroyEffect.h"
#include "ItemPower.h"

constexpr auto OwnSpeed = 0.08f;
constexpr auto AnimationDefaultId = "df";
constexpr auto DetectedPlayerRadius = 130.0f;
constexpr auto AttackRadius = 100;
constexpr auto MaxStepMove = 60;
constexpr auto RateDropItemPower = 0.2;
constexpr auto DelayAttackingTime = 6000;

void CEnemyStuka::OnFreeFlying()
{
	auto now = GetTickCount64();
	Vector2D playerPos = CPlayer::GetInstance()->GetPlayer()->GetPosition();
	if (PositionsDistance(this->position, playerPos) < AttackRadius
		&& this->position.y > playerPos.y
		&& now - this->dwPrevAttackTime > DelayAttackingTime) {
		this->state = EStukaState::ATTACKING;
		this->attackFromY = this->position.y;
	}
}

void CEnemyStuka::OnBackFlying()
{
	if (abs(this->position.y - this->attackFromY) > 5.0f) {
		this->velocity.y = OwnSpeed - 0.02;
	}
	else {
		this->velocity.y = 0;
		this->state = EStukaState::FREE_FLYING;
	}
}

void CEnemyStuka::OnAttacking()
{
	Vector2D playerPos = CPlayer::GetInstance()->GetPlayer()->GetPosition();
	if (PositionsDistance(this->position, playerPos) < AttackRadius) {
		this->velocity = NormalizeVector(playerPos - this->position) * OwnSpeed;
	}
	else {
		this->state = EStukaState::BACK_FLYING;
		if (this->velocity.x < 0) {
			this->velocity.x = -OwnSpeed;
		}
		else {
			this->velocity.x = OwnSpeed;
		}
	}
}

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
		this->velocity.x = this->nx * OwnSpeed;
	}

	switch (this->state)
	{
	case EStukaState::FREE_FLYING:
		this->OnFreeFlying();
		break;
	
	case EStukaState::ATTACKING:
		this->OnAttacking();
		break;

	case EStukaState::BACK_FLYING:
		this->OnBackFlying();
		break;
	}
}

void CEnemyStuka::Render()
{
	animations.at(AnimationDefaultId)->Render(this->position, 1, DrawArgbColorDefault());
}

void CEnemyStuka::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CCharaterBase*>(other)) {
		other->TakeDamage(this->damage);
		this->TakeDamage(other->GetDamage());

		STriggerTag tag = STriggerTag(other);
		other->AddTriggerTag(this);
		this->AddTriggerTag(other);

		this->state = EStukaState::BACK_FLYING;
		this->dwPrevAttackTime = GetTickCount64();
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
