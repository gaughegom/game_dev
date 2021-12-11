#include "SophiaBullet.h"
#include "Brick.h"
#include "Player.h"

#define V_BULLET_BOXSIZE_HORIZON	Vector2D(22, 6)
#define	V_BULLET_BOXSIZE_VERTICAL	Vector2D(6, 22)

#define SPR_DEFAULT_ID	"df"

CSophiaBullet::CSophiaBullet(int direct)
{
	this->damage = 10;

	/*
		collider of bullet
	*/
	auto collider = new CCollider2D(this, true, false);
	collider->SetOffset(VectorZero());
	
	// boxsize, velocity, sprite
	auto sprites = CSprites::GetInstance();
	if (direct == 0) {
		collider->SetBoxSize(V_BULLET_BOXSIZE_VERTICAL);
		this->velocity = Vector2D(0, SOPHIA_BASICBULLET_VELOCITY);
		this->AddSprite(SPR_DEFAULT_ID, "sprSBullet01");
		this->nx = 1;
	}
	else {
		collider->SetBoxSize(V_BULLET_BOXSIZE_HORIZON);
		this->AddSprite(SPR_DEFAULT_ID, "sprSBullet00");
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
	// delete when out of camera
	auto camera = CCamera::GetInstance();
	if (!camera->GetBoundingBox().Contain(this->colliders.at(0)->GetBoundingBox())) {
		this->OnDelete();
	}
}

void CSophiaBullet::Render()
{
	auto sprite = this->sprites.at(SPR_DEFAULT_ID);
	sprite->Draw(this->position, this->nx, DRAW_COLOR_DEFAULT);
}

void CSophiaBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CSophia*>(coEvent->object)
		|| dynamic_cast<CBrick*>(coEvent->object)
		|| dynamic_cast<CSophiaBullet*>(coEvent->object)) {
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
