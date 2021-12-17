#include "EnemyStuka.h"
#include "Player.h"

constexpr auto ANIMATION_DEFAULT_ID = "df";
constexpr auto DETACTED_PLAYER_DISTANCE = 130.0f;

CEnemyStuka::CEnemyStuka()
{
	this->AddAnimation(ANIMATION_DEFAULT_ID, "aniEStuka");
	this->hp = 10;
	this->damage = 10;

	this->active = false;

	//
	this->colliders.clear();
	auto collider = new CCollider2D(this, true, true, VectorZero(), V_STUKA_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);

}

void CEnemyStuka::Update(DWORD dt)
{
	this->ScheduleActiveByDistance(DETACTED_PLAYER_DISTANCE);

	if (this->active) {
		this->velocity.x = this->nx * ENEMY_VELOCITY_NORMAL;
		InHorizontalMove(this, dt);
	}
}

void CEnemyStuka::Render()
{
	animations.at(ANIMATION_DEFAULT_ID)->Render(this->position, 1, DRAW_COLOR_DEFAULT);
}

void CEnemyStuka::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CEnemyStuka::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CSophia*>(coEvent->object)) {
		coEvent->object->TakeDamage(this->damage);
		this->TakeDamage(coEvent->object->GetDamage());
	}
}
