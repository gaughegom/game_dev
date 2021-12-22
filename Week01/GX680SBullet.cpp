#include "GX680SBullet.h"
#include "SmallDestroyEffect.h"
#include "Player.h"
#include "Mortar.h"
#include "BigJasonBullet.h"

constexpr auto SpriteDefaultId = "df";
constexpr auto OwnSpeed = 0.05f;


CGX680SBullet::CGX680SBullet()
{
	this->AddSprite(SpriteDefaultId, "sprEGX680Bullet");
	this->damage = 10;

	//
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), Vector2D(8.0f, 8.0f));
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CGX680SBullet::Update(DWORD dt)
{
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CSmallDestroyEffect>(this->position);
		return;
	}

	Vector2D vDistance = CPlayer::GetInstance()->GetPlayer()->GetPosition() - this->position;
	if (vDistance.x != 0) vDistance.x = vDistance.x / abs(vDistance.x);
	if (vDistance.y != 0) vDistance.y = vDistance.y / abs(vDistance.y);

	this->velocity.x = vDistance.x * OwnSpeed;
	this->velocity.y = vDistance.y * OwnSpeed;
}

void CGX680SBullet::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->sprites.at(SpriteDefaultId)->Draw(this->position, this->nx, color, DrawLayer01);
}

void CGX680SBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CBrick*>(other) || dynamic_cast<CMortar*>(other)) {
		this->hp = 0;
	}
	else if (dynamic_cast<CCharaterBase*>(other)) {
		other->TakeDamage(this->damage);
		this->hp = 0;
	}
	else if (dynamic_cast<CBigJasonBullet*>(other)) {
		this->hp = 0;
	}
	else if (dynamic_cast<CEnemyBase*>(other) || dynamic_cast<CGX680SBullet*>(other)) {
		STriggerTag tag = STriggerTag(other);
		other->AddTriggerTag(this);
		this->AddTriggerTag(other);
	}
}
