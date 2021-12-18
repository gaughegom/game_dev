#include "BigJasonBullet.h"
#include "Camera.h"
#include "Brick.h"
#include "EnemyGX-680.h"
#include "EnemyGX-680S.h"
#include "SmallDestroyEffect.h"

#define V_BOXSIZE_HORIZON			Vector2D(8.0f, 6.0f)
#define V_BOXSIZE_VERTICAL			Vector2D(6.0f, 6.0f)

constexpr auto BulletSpeed		= 0.2f;
constexpr auto SpriteDefaultId	= "df";

CBigJasonBullet::CBigJasonBullet(BigJasonBulletDirection state)
{
	this->directState = state;
	this->damage = 10;

	CCollider2D* collider = new CCollider2D(this, true, false);
	collider->SetOffset(VectorZero());
	switch (this->directState)
	{
	case BigJasonBulletDirection::LEFT:
		this->AddSprite(SpriteDefaultId, "sprBJBullet00");
		this->velocity.x = -BulletSpeed;
		this->nx = -1;
		collider->SetBoxSize(V_BOXSIZE_HORIZON);
		break;

	case BigJasonBulletDirection::RIGHT:
		this->AddSprite(SpriteDefaultId, "sprBJBullet00");
		this->velocity.x = BulletSpeed;
		this->nx = 1;
		collider->SetBoxSize(V_BOXSIZE_HORIZON);
		break;

	case BigJasonBulletDirection::UP:
		this->AddSprite(SpriteDefaultId, "sprBJBullet01");
		this->velocity.y = BulletSpeed;
		this->nx = 1;
		collider->SetBoxSize(V_BOXSIZE_VERTICAL);
		break;

	case BigJasonBulletDirection::DOWN:
		this->AddSprite(SpriteDefaultId, "sprBJBullet01");
		this->velocity.y = -BulletSpeed;
		this->nx = -1;
		collider->SetBoxSize(V_BOXSIZE_VERTICAL);
		break;

	default:
		break;
	}
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CBigJasonBullet::Update(DWORD dt)
{
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CSmallDestroyEffect>(this->position);
		return;
	}

	auto camera = CCamera::GetInstance();
	if (!camera->GetBoundingBox().Contain(this->colliders.at(0)->GetBoundingBox())) {
		this->hp = 0;
	}
}

void CBigJasonBullet::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->sprites.at(SpriteDefaultId)->Draw(this->position, this->nx, color);
}

void CBigJasonBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CBrick*>(coEvent->object)
		|| dynamic_cast<CBigJasonBullet*>(coEvent->object)) {
		this->hp = 0;
	}
	else if (dynamic_cast<CEnemyGX680*>(coEvent->object)
		|| dynamic_cast<CEnemyGX680S*>(coEvent->object)) {
		coEvent->object->TakeDamage(this->damage);
		this->hp = 0;
	}
}

void CBigJasonBullet::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
