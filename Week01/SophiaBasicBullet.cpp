#include "SophiaBasicBullet.h"
#include "Brick.h"
#include "ControllerObject.h"

CSophiaBasicBullet::CSophiaBasicBullet(int direct)
{
	this->damage = 10;

	/*
		collider of bullet
	*/
	auto collider = new CCollider2D;
	collider->SetGameObject(this);
	collider->SetOffset(VectorZero());
	collider->SetDynamic(true);
	
	// boxsize, velocity
	if (direct == 0) {
		collider->SetBoxSize(V_BULLET_BOXSIZE_VERTICAL);
		this->velocity = Vector2D(0, BULLET_VELOCITY);
		this->nx = 1;
	}
	else {
		collider->SetBoxSize(V_BULLET_BOXSIZE_HORIZON);
		if (direct == 1) {
			this->velocity = Vector2D(BULLET_VELOCITY, 0);
			this->nx = -1;
		}
		else if (direct == -1) {
			this->velocity = Vector2D(-BULLET_VELOCITY, 0);
			this->nx = 1;
		}
	}

	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CSophiaBasicBullet::Update(DWORD dt)
{
	// delete when out of distance
	auto sophia = CControllerObject::GetInstance()->GetSophia();
	Vector2D sophiaPos = sophia->GetPosition();
	float distance = PositionsDistance(this->position, sophiaPos);
	if (distance > 400) {
		this->OnDelete();
	}
}

void CSophiaBasicBullet::Render()
{
	auto sprites = CSprites::GetInstance();
	CSprite* sprite;
	if (this->velocity.y > 0) {
		sprite = sprites->Get(12); // 12: bullet up
	}
	else {
		sprite = sprites->Get(11); // 11: horizon
	}

	sprite->Draw(this->position, this->nx, 255);
}

void CSophiaBasicBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CBrick*>(coEvent->object)) {
		this->OnDelete();
	}
	else if (dynamic_cast<CSophiaBasicBullet*>(coEvent->object)) {
		this->OnDelete();
	}
}

void CSophiaBasicBullet::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CSophiaBasicBullet::OnDelete()
{
	this->deleted = true;
	auto controller = CControllerObject::GetInstance();
	if (controller->GetSelectId() == ControllerObjectID::SOPHIA) {
		controller->GetSophia()->DecreaseBullet();
	}
}

CSophiaBasicBullet::~CSophiaBasicBullet()
{
}
