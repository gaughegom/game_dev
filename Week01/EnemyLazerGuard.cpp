#include "EnemyLazerGuard.h"
#include "BigDestroyEffect.h"
#include "Player.h"
#include "BigJasonBullet.h"
#include "LazerGuardBullet.h"

constexpr auto AnimationDefaultId = "df";
constexpr auto OwnSpeed = 0.06f;
constexpr auto DetectedPlayerXAsix = 250.0f;
constexpr auto DelayAttackTime = 4000;

CEnemyLazerGuard::CEnemyLazerGuard()
{
	this->AddAnimation(AnimationDefaultId, "aniELazer");

	this->damage = 10;
	this->hp = 30;

	//
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), Vector2D(17.0f, 17.0f));
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyLazerGuard::Update(DWORD dt)
{
	if (this->IsLive() == false) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		return;
	}

	LPGAMEOBJECT player = CPlayer::GetInstance()->GetPlayer();
	if (abs(this->position.x - player->GetPosition().x) < DetectedPlayerXAsix
		&& this->position.y > player->GetPosition().y) {
		this->velocity.x = this->nx * OwnSpeed;

		auto now = GetTickCount64();
		if (now - this->prevAttackTime > DelayAttackTime) {
			CGame::GetInstance()->InitiateAndPushToQueue<CLazerGuardBullet>(this->position);
			this->prevAttackTime = now;
		}
	}
}

void CEnemyLazerGuard::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->animations.at(AnimationDefaultId)->Render(this->position, this->nx, color);
}

void CEnemyLazerGuard::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;

	if (dynamic_cast<CBrick*>(other)) {

		DebugOut(L"lazer guard reverse %f\n", this->nx);

		this->nx = -this->nx;
	}
	else if (dynamic_cast<CCharaterBase*>(other)) {
		other->TakeDamage(this->damage);
		this->TakeDamage(other->GetDamage());

		STriggerTag tag = STriggerTag(other);
		other->AddTriggerTag(this);
		this->AddTriggerTag(other);
	}
	else if (dynamic_cast<CBigJasonBullet*>(other)) {
		this->TakeDamage(other->GetDamage());
		other->SetHp(0);
	}


}
