#include "EnemyBallbomb.h"
#include "Brick.h"
#include "Sophia.h"
#include "SophiaBullet.h"
#include "BigDestroyEffect.h"

#define V_BOXSIZE			Vector2D(10.0f, 10.0f)

constexpr auto SpriteDefaultId = "df";
constexpr auto LifeTime = 2000;


CEnemyBallbomb::CEnemyBallbomb()
{
	this->AddSprite(SpriteDefaultId, "sprBallbomb");
	
	this->damage = 5;
	this->hp = 10;
	this->ground = false;

	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyBallbomb::Update(DWORD dt)
{
	InGravityAffect(this, dt);

	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		return;
	}

	// check lifetime
	if (GetTickCount64() - this->bornTime > LifeTime) {
		this->hp = 0;
	}
}

void CEnemyBallbomb::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->sprites.at(SpriteDefaultId)->Draw(this->position, this->nx, color);
}

void CEnemyBallbomb::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CBrick*>(other) && this->ground == false) {
		this->ground = true;
	}
	else if (dynamic_cast<CEnemyBallbomb*>(other)) {
		STriggerTag tag = STriggerTag(other);
		other->AddTriggerTag(this);
		this->AddTriggerTag(other);
	}
}

void CEnemyBallbomb::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
