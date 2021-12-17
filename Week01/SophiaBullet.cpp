#include "SophiaBullet.h"
#include "Brick.h"
#include "Player.h"
#include "EnemyBallcarry.h"
#include "EnemyInterrupt.h"
#include "EnemyStuka.h"
#include "EnemyBallot.h"
#include "SmallDestroyEffect.h"

#define V_BULLET_HORIZONAL_BOXSIZE		Vector2D(22, 6)
#define	V_BULLET_VERTICAL_BOXSIZE		Vector2D(6, 22)

constexpr auto SpriteDefaultId = "df";
constexpr auto BulletSpeed = 0.2f;

CSophiaBullet::CSophiaBullet(int direct)
{
	this->damage = 10;

	/*
		collider of bullet
	*/
	CCollider2D* collider = new CCollider2D(this, true, false);
	collider->SetOffset(VectorZero());
	
	// boxsize, velocity, sprite
	CSprites* sprites = CSprites::GetInstance();
	if (direct == 0) {
		collider->SetBoxSize(V_BULLET_VERTICAL_BOXSIZE);
		this->velocity = Vector2D(0, BulletSpeed);
		this->AddSprite(SpriteDefaultId, "sprSBullet01");
		this->nx = 1;
	}
	else {
		collider->SetBoxSize(V_BULLET_HORIZONAL_BOXSIZE);
		this->AddSprite(SpriteDefaultId, "sprSBullet00");
		if (direct == 1) {
			this->velocity = Vector2D(BulletSpeed, 0);
			this->nx = -1;
		}
		else if (direct == -1) {
			this->velocity = Vector2D(-BulletSpeed, 0);
			this->nx = 1;
		}
	}
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CSophiaBullet::Update(DWORD dt)
{
	// delete when out of distance
	/*auto sophia = CPlayer::GetInstance()->GetSophia();
	Vector2D sophiaPos = sophia->GetPosition();
	float distance = PositionsDistance(this->position, sophiaPos);
	if (distance > 300) {
		this->OnDelete();
	}*/
	// delete when out of g_camera
	auto camera = CCamera::GetInstance();
	if (!camera->GetBoundingBox().Contain(this->colliders.at(0)->GetBoundingBox())) {
		this->OnDelete();
	}

	// effect destroy
	if (this->IsLive() == false) {
		LPGAMEOBJECT destroyEffect = nullptr;
		destroyEffect = new CSmallDestroyEffect;

		Vector2D boxSize = this->colliders.at(0)->GetBoxSize();
		if (boxSize.x > boxSize.y) {
			destroyEffect->SetPosition(this->position + Vector2D(-this->nx * boxSize.x / 2, 0));
		}
		else {
			destroyEffect->SetPosition(this->position + Vector2D(0, boxSize.y / 2));
		}

		CGame::GetInstance()->NewGameObject(destroyEffect);
	}
}

void CSophiaBullet::Render()
{
	LPSPRITE sprite = this->sprites.at(SpriteDefaultId);
	sprite->Draw(this->position, this->nx, DRAW_COLOR_DEFAULT);
}

void CSophiaBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CSophia*>(other)
		|| dynamic_cast<CBrick*>(other)
		|| dynamic_cast<CSophiaBullet*>(other)) {
		this->OnDelete();
	}
	else if (dynamic_cast<CEnemyBallcarry*>(other)
		|| dynamic_cast<CEnemyInterrupt*>(other)
		|| dynamic_cast<CEnemyEyelet*>(other)
		|| dynamic_cast<CEnemyStuka*>(other)
		|| dynamic_cast<CEnemyBallot*>(other)) {
		other->TakeDamage(this->damage);
		this->OnDelete();
	}
}

void CSophiaBullet::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CSophiaBullet::OnDelete()
{
	this->hp = 0;	// auto destroy bullet when collision
	auto controller = CPlayer::GetInstance();
	if (controller->GetSelectId() == PlayerCharacterId::SOPHIA) {
		controller->GetSophia()->DecreaseBullet();	// decrease bullet of sophia
	}
}
