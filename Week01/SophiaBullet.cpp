#include "SophiaBullet.h"
#include "Brick.h"
#include "Player.h"
#include "EnemyBallcarry.h"
#include "EnemyInterrupt.h"
#include "EnemyStuka.h"
#include "EnemyBallot.h"

#define V_BULLET_BOXSIZE_HORIZON	Vector2D(22, 6)
#define	V_BULLET_BOXSIZE_VERTICAL	Vector2D(6, 22)

#define SPRITE_DEFAULT_ID		"df"
#define SPRITE_DESTROY_ID		"destroy"
#define ANIMATION_DESTROY_ID	"destroy"

CSophiaBullet::CSophiaBullet(int direct)
{
	this->damage = 10;

	/*
		collider of bullet
	*/
	CCollider2D* collider = new CCollider2D(this, true, false);
	collider->SetOffset(VectorZero());
	
	// boxsize, velocity, sprite
	this->AddAnimation(ANIMATION_DESTROY_ID, "aniSmallDestroy");
	CSprites* sprites = CSprites::GetInstance();
	this->AddSprite(SPRITE_DESTROY_ID, "sprDestroy02");
	if (direct == 0) {
		collider->SetBoxSize(V_BULLET_BOXSIZE_VERTICAL);
		this->velocity = Vector2D(0, SOPHIA_BASICBULLET_VELOCITY);
		this->AddSprite(SPRITE_DEFAULT_ID, "sprSBullet01");
		this->nx = 1;
	}
	else {
		collider->SetBoxSize(V_BULLET_BOXSIZE_HORIZON);
		this->AddSprite(SPRITE_DEFAULT_ID, "sprSBullet00");
		if (direct == 1) {
			this->velocity = Vector2D(SOPHIA_BASICBULLET_VELOCITY, 0);
			this->nx = -1;
		}
		else if (direct == -1) {
			this->velocity = Vector2D(-SOPHIA_BASICBULLET_VELOCITY, 0);
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
}

void CSophiaBullet::Render()
{
	LPSPRITE sprite = this->sprites.at(SPRITE_DEFAULT_ID);
	sprite->Draw(this->position, this->nx, DRAW_COLOR_DEFAULT);
}

void CSophiaBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CSophia*>(coEvent->object)
		|| dynamic_cast<CBrick*>(coEvent->object)
		|| dynamic_cast<CSophiaBullet*>(coEvent->object)) {
		this->OnDelete();
	}
	else if (dynamic_cast<CEnemyBallcarry*>(coEvent->object)
		|| dynamic_cast<CEnemyInterrupt*>(coEvent->object)
		|| dynamic_cast<CEnemyEyelet*>(coEvent->object)
		|| dynamic_cast<CEnemyStuka*>(coEvent->object)
		|| dynamic_cast<CEnemyBallot*>(coEvent->object)) {
		coEvent->object->TakeDamage(this->damage);
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

CSophiaBullet::~CSophiaBullet()
{
}
