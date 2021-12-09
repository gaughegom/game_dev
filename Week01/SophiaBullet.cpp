#include "SophiaBullet.h"
#include "Brick.h"
#include "ControllerObject.h"

CSophiaBullet::CSophiaBullet(int direct)
{
	this->damage = 10;

	/*
		collider of bullet
	*/
	auto collider = new CCollider2D;
	collider->SetGameObject(this);
	collider->SetOffset(VectorZero());
	collider->SetDynamic(true);
	
	// boxsize, velocity, sprite
	auto sprites = CSprites::GetInstance();
	if (direct == 0) {
		collider->SetBoxSize(V_BULLET_BOXSIZE_VERTICAL);
		this->velocity = Vector2D(0, SOPHIA_BASICBULLET_VELOCITY);
		this->sprite = sprites->Get(14); // 14: bullet vertical
		this->nx = 1;
	}
	else {
		collider->SetBoxSize(V_BULLET_BOXSIZE_HORIZON);
		this->sprite = sprites->Get(13); // 13: bullet horizon
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
	/*auto sophia = CControllerObject::GetInstance()->GetSophia();
	Vector2D sophiaPos = sophia->GetPosition();
	float distance = PositionsDistance(this->position, sophiaPos);
	if (distance > 150) {
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
	this->sprite->Draw(this->position, this->nx, DRAW_COLOR_DEFAULT);
}

void CSophiaBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	this->OnDelete();
}

void CSophiaBullet::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CSophiaBullet::OnDelete()
{
	this->hp = 0;	// auto destroy bullet when collision
	auto controller = CControllerObject::GetInstance();
	if (controller->GetSelectId() == ControllerObjectID::SOPHIA) {
		controller->GetSophia()->DecreaseBullet();	// decrease bullet of sophia
	}
}

CSophiaBullet::~CSophiaBullet()
{
}
