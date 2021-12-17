#include "EnemyBallot.h"
#include "Player.h"

#define	V_BOXSIZE			Vector2D(18, 18)

constexpr auto ANIMATION_DEFAULT_ID = "default";
constexpr auto SPR_IDLE_ID = "idle";

CEnemyBallot::CEnemyBallot()
{
	this->AddAnimation(ANIMATION_DEFAULT_ID, "aniEBallot");		// animation
	this->AddSprite(SPR_IDLE_ID, "sprEBallot00");		// for idle state

	// hp, damage
	this->hp = 20;
	this->damage = 10;

	// collider
	this->colliders.clear();
	auto collider = new CCollider2D(this, true, false, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyBallot::Update(DWORD dt)
{
}

void CEnemyBallot::Render()
{
	auto color = this->GetRenderColor();
	auto player = CPlayer::GetInstance()->GetPlayer();
	if (abs(this->position.x - player->GetPosition().x) < 60) {
		this->animations.at(ANIMATION_DEFAULT_ID)->Render(this->position, this->nx, color);
	}
	else {
		this->sprites.at(SPR_IDLE_ID)->Draw(this->position, this->nx, color);
	}
}

void CEnemyBallot::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CSophia*>(coEvent->object)) {
		coEvent->object->TakeDamage(this->damage);
		this->TakeDamage(coEvent->object->GetDamage());
	}
}

void CEnemyBallot::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
