#include "EnemyBallot.h"
#include "SophiaBullet.h"
#include "ControllerObject.h"

CEnemyBallot::CEnemyBallot()
{
	this->AddAnimation(BALLOT_DEFAULT_ANIMATION, 250);		// animation
	this->AddSprite(BALLOT_DEFAULT_SPRITE_IDLE, 250);		// for idle state

	// hp, damage
	this->hp = 20;
	this->damage = 10;

	// collider
	this->colliders.clear();
	auto collider = new CCollider2D;
	collider->SetGameObject(this);
	collider->SetOffset(VectorZero());
	collider->SetBoxSize(V_BALLOT_BOXSIZE);
	collider->SetDynamic(true);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyBallot::Update(DWORD dt)
{
}

void CEnemyBallot::Render()
{
	auto sophia = CControllerObject::GetInstance()->GetSophia();
	if (abs(this->position.x - sophia->GetPosition().x) < 60) {
		this->animations.at(BALLOT_DEFAULT_ANIMATION)->Render(this->position, this->nx, 255);
	}
	else {
		this->sprites.at(BALLOT_DEFAULT_SPRITE_IDLE)->Draw(this->position, this->nx, 255);
	}
}

void CEnemyBallot::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CSophiaBullet*>(coEvent->object)) {
		this->TakeDamage(coEvent->object);
	}
}

void CEnemyBallot::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
