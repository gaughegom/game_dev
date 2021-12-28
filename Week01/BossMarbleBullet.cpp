#include "BossMarbleBullet.h"
#include "SmallDestroyEffect.h"
#include "CharacterBase.h"
#include "Brick.h"
#include "EnemyBase.h"
#include "Boss.h"

constexpr auto SpriteDefaultId = "df";

CBossMarbleBullet::CBossMarbleBullet()
{
	this->AddSprite(SpriteDefaultId, "sprMarbleBullet");

	this->damage = 10;

	//
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), Vector2D(10.0f, 10.0f));
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CBossMarbleBullet::Update(DWORD dt)
{
	if (this->IsLive() == false) {
		CGame::GetInstance()->InitiateAndPushToQueue<CSmallDestroyEffect>(this->position);
		return;
	}
}

void CBossMarbleBullet::Render()
{
	this->sprites.at(SpriteDefaultId)->Draw(this->position, this->nx, DrawArgbColorDefault());
}

void CBossMarbleBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;

	if (dynamic_cast<CCharaterBase*>(other)) {
		other->TakeDamage(this->damage);
		this->SetHp(0);
	}
	else if (dynamic_cast<CBrick*>(other)) {
		this->SetHp(0);
	}
	else if (dynamic_cast<CEnemyBase*>(other)
		|| dynamic_cast<CBulletBase*>(other)
		|| dynamic_cast<CBoss*>(other)) {
		STriggerTag tag = STriggerTag(other);
		other->AddTriggerTag(this);
		this->AddTriggerTag(other);
	}
}
