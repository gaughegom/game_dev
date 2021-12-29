#include "SophiaBullet.h"
#include "Brick.h"
#include "Player.h"
#include "EnemyBase.h"
#include "SmallDestroyEffect.h"

#define V_BULLET_HORIZONAL_BOXSIZE		Vector2D(22, 6)
#define	V_BULLET_VERTICAL_BOXSIZE		Vector2D(6, 22)

constexpr auto SpriteDefaultId = "df";
constexpr auto Speed = 0.2f;
constexpr auto BasicDamage = 10;

CSophiaBullet::CSophiaBullet(int direct)
{
	// damage
	LPGAMEOBJECT sophia = CPlayer::GetInstance()->GetSophia();
	this->damage = sophia->GetLevel() * BasicDamage + sophia->GetBonusDamage();

	//
	CCollider2D* collider = new CCollider2D(this, true, false);
	collider->SetOffset(VectorZero());
	
	// boxsize, velocity, sprite
	CSprites* sprites = CSprites::GetInstance();
	if (direct == 0) {
		collider->SetBoxSize(V_BULLET_VERTICAL_BOXSIZE);
		this->velocity = Vector2D(0, Speed);
		this->AddSprite(SpriteDefaultId, "sprSBullet01");
		this->nx = 1;
	}
	else {
		collider->SetBoxSize(V_BULLET_HORIZONAL_BOXSIZE);
		this->AddSprite(SpriteDefaultId, "sprSBullet00");
		if (direct == 1) {
			this->velocity = Vector2D(Speed, 0);
			this->nx = -1;
		}
		else if (direct == -1) {
			this->velocity = Vector2D(-Speed, 0);
			this->nx = 1;
		}
	}
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CSophiaBullet::Update(DWORD dt)
{
	// delete when out of distance
	auto player = CPlayer::GetInstance()->GetSophia();
	Vector2D playerPos = player->GetPosition();
	float distance = PositionsDistance(this->position, playerPos);
	if (distance > 300) {
		this->OnDelete();
	}

	// effect destroy
	if (this->IsLive() == false) {
		LPGAMEOBJECT destroyEffect = nullptr;
		destroyEffect = new CSmallDestroyEffect;

		Vector2D boxSize = this->colliders.at(0)->GetBoxSize();
		if (boxSize.x > boxSize.y) {
			destroyEffect->SetPosition(this->position + Vector2D(-this->nx * boxSize.x / 4, 0));
		}
		else {
			destroyEffect->SetPosition(this->position + Vector2D(0, boxSize.y / 4));
		}

		CGame::GetInstance()->PushToQueueObject(destroyEffect);
		CSound::GetInstance()->PlayWaveFile("bulletDestroy");
	}
}

void CSophiaBullet::Render()
{
	LPSPRITE sprite = this->sprites.at(SpriteDefaultId);
	sprite->Draw(this->position, this->nx, DrawArgbColorDefault());
}

void CSophiaBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CCharaterBase*>(other)
		|| dynamic_cast<CBrick*>(other)
		|| dynamic_cast<CSophiaBullet*>(other)) {
		this->OnDelete();
	}
	else if (dynamic_cast<CEnemyBase*>(other)) {
		other->TakeDamage(this->damage);
		this->OnDelete();
	}
}

void CSophiaBullet::OnDelete()
{
	this->hp = 0;	// auto destroy bullet when collision
	auto controller = CPlayer::GetInstance();
	if (controller->GetSelectId() == PlayerCharacterId::SOPHIA) {
		controller->GetSophia()->DecreaseBullet();	// decrease bullet of sophia
	}
}
