#include "BigJasonBullet.h"
#include "Camera.h"
#include "Brick.h"
#include "EnemyGX-680.h"
#include "EnemyGX-680S.h"
#include "SmallDestroyEffect.h"
#include "Mortar.h"
#include "Player.h"

#define V_BOXSIZE_HORIZON			Vector2D(8.0f, 6.0f)
#define V_BOXSIZE_VERTICAL			Vector2D(6.0f, 6.0f)

constexpr auto Speed		= 0.4f;
constexpr auto SpriteDefaultId	= "df";
constexpr auto DurationInit = 15;
constexpr auto Amplitude = 14.0f;
constexpr auto Frequecy = 5.0f;

CBigJasonBullet::CBigJasonBullet(BigJasonBulletDirection state)
{
	this->directState = state;
	LPGAMEOBJECT bigJason = CPlayer::GetInstance()->GetBigJason();
	this->damage = 10 * bigJason->GetLevel() + bigJason->GetBonusDamage();

	CCollider2D* collider = new CCollider2D(this, true, false);
	collider->SetOffset(VectorZero());
	switch (this->directState)
	{
	case BigJasonBulletDirection::LEFT:
		this->AddSprite(SpriteDefaultId, "sprBJBullet00");
		this->velocity.x = -Speed;
		this->nx = -1;
		collider->SetBoxSize(V_BOXSIZE_HORIZON);
		break;

	case BigJasonBulletDirection::RIGHT:
		this->AddSprite(SpriteDefaultId, "sprBJBullet00");
		this->velocity.x = Speed;
		this->nx = 1;
		collider->SetBoxSize(V_BOXSIZE_HORIZON);
		break;

	case BigJasonBulletDirection::UP:
		this->AddSprite(SpriteDefaultId, "sprBJBullet01");
		this->velocity.y = Speed;
		this->nx = 1;
		collider->SetBoxSize(V_BOXSIZE_VERTICAL);
		break;

	case BigJasonBulletDirection::DOWN:
		this->AddSprite(SpriteDefaultId, "sprBJBullet01");
		this->velocity.y = -Speed;
		this->nx = -1;
		collider->SetBoxSize(V_BOXSIZE_VERTICAL);
		break;

	default:
		break;
	}
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);

	//
	this->angular = Random(0, 360);
}

void CBigJasonBullet::Update(DWORD dt)
{
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CSmallDestroyEffect>(this->position);
		return;
	}

	if (inSinWave == false) {
		if (GetTickCount64() - this->initTime > DurationInit) {
			this->inSinWave = true;
		}
	}
	else {
		// move pattern in sin wave
		if (this->velocity.x != 0) {
			InSinWaveXAsix(this, dt, 5.0f, 14.0f);
		}
		else if (this->velocity.y != 0) {
			InSinWaveYAsix(this, dt, 5.0f, 14.0f);
		}
	}


	auto camera = CCamera::GetInstance();
	if (!camera->GetBoundingBox().Contain(this->colliders.at(0)->GetBoundingBox())) {
		this->hp = 0;
	}
}

void CBigJasonBullet::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->sprites.at(SpriteDefaultId)->Draw(this->position, this->nx, color, DrawLayer01);
}

void CBigJasonBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CBrick*>(other)
		|| dynamic_cast<CBigJasonBullet*>(other)) {
		this->hp = 0;
	}
	else if (dynamic_cast<CEnemyBase*>(other)) {
		other->TakeDamage(this->damage);
		this->hp = 0;
	}
	else if (dynamic_cast<CMortar*>(other)) {
		other->TakeDamage(this->damage);
		this->hp = 0;
	}
}

