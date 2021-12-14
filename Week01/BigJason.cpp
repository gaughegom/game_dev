#include "BigJason.h"

#define BOXSIZE_HORIZON				Vector2D(24.0f, 32.0f)
#define BOXSIZE_VERTICAL			Vector2D(20.0f, 32.0f)

#define ANIMATION_WALK_HORIZON_ID	"walk-horizon"
#define ANIMATION_WALK_UP_ID		"walk-up"
#define ANIMATION_WALK_DOWN_ID		"walk-down"
#define SPRITE_STAY_HORIZON_ID		"stay-horizon"
#define SPRITE_STAY_UP_ID			"stay-up"
#define SPRITE_STAY_DOWN_ID			"stay-down"

CBigJason::CBigJason()
{
	// init aniamtion, sprite
	this->AddAnimation(ANIMATION_WALK_HORIZON_ID, "aniBJHorizon");
	this->AddAnimation(ANIMATION_WALK_UP_ID, "aniBJUpward");
	this->AddAnimation(ANIMATION_WALK_DOWN_ID, "aniBJDownward");
	this->AddSprite(SPRITE_STAY_HORIZON_ID, "sprBJHorizon01");
	this->AddSprite(SPRITE_STAY_UP_ID, "sprBJUpward01");
	this->AddSprite(SPRITE_STAY_DOWN_ID, "sprBJDownward01");

	// velocity
	this->directState = BigJasonDirectState::STAY;
	this->velocity = VectorZero();
	this->hp = 100;
	this->damage = 0;

	// init collider
	this->colliders.clear();
	CCollider2D* collider = new CCollider2D(
		this, true, false, 
		VectorZero(), BOXSIZE_VERTICAL);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CBigJason::Update(DWORD dt)
{
	// not in gravity
}

void CBigJason::Render()
{
	// get render color
	auto color = this->GetRenderColor();

	if (this->directState == BigJasonDirectState::STAY) {
		// render sprite by key currentSpriteState
	}
	else {
		// mapping animation key

		// render animation
	}
}

void CBigJason::ListenKeyEvent()
{
}

void CBigJason::UpdateColliders()
{
}

void CBigJason::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CBigJason::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
