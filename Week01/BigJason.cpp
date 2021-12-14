#include "BigJason.h"
#include "Player.h"

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
	this->currentSpriteState = SPRITE_STAY_DOWN_ID;
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
	// TODO: update collider

	if (CPlayer::GetInstance()->GetSelectId() == PlayerCharacterId::BIGJASON) {
		this->ListenKeyEvent();
	}
}

void CBigJason::Render()
{
	// get render color
	auto color = this->GetRenderColor();

	if (this->directState == BigJasonDirectState::STAY) {
		this->sprites.at(this->currentSpriteState)->Draw(this->position, -this->nx, color);
	}
	else {
		std::string aniKey = this->MappingStateOfAnimation();
		this->animations.at(aniKey)->Render(this->position, -this->nx, color);
	}
}

void CBigJason::ListenKeyEvent()
{
	auto input = CInputHandler::GetInstance();

	// map direct state
	if (input->IsKeyDown(DIK_RIGHT)) {
		this->SubcribeDirectState(BigJasonDirectState::RIGHTWALK);
	}
	else if (input->IsKeyDown(DIK_LEFT)) {
		this->SubcribeDirectState(BigJasonDirectState::LEFTWALK);
	}
	else if (input->IsKeyDown(DIK_UP)) {
		this->SubcribeDirectState(BigJasonDirectState::UPWALK);
	}
	else if (input->IsKeyDown(DIK_DOWN)) {
		this->SubcribeDirectState(BigJasonDirectState::DOWNWALK);
	}
	else {
		this->SubcribeDirectState(BigJasonDirectState::STAY);
	}
}

void CBigJason::UpdateColliders()
{
}

std::string CBigJason::MappingStateOfAnimation()
{
	switch (this->directState)
	{
	case BigJasonDirectState::LEFTWALK:
		this->currentSpriteState = SPRITE_STAY_HORIZON_ID;
		return ANIMATION_WALK_HORIZON_ID;

	case BigJasonDirectState::RIGHTWALK:
		this->currentSpriteState = SPRITE_STAY_HORIZON_ID;
		return ANIMATION_WALK_HORIZON_ID;

	case BigJasonDirectState::UPWALK:
		this->currentSpriteState = SPRITE_STAY_UP_ID;
		return ANIMATION_WALK_UP_ID;

	case BigJasonDirectState::DOWNWALK:
		this->currentSpriteState = SPRITE_STAY_DOWN_ID;
		return ANIMATION_WALK_DOWN_ID;
	default:
		break;
	}
}

void CBigJason::SubcribeDirectState(BigJasonDirectState newState)
{
	switch (newState)
	{
	case BigJasonDirectState::STAY:
		this->directState = BigJasonDirectState::STAY;
		this->velocity = VectorZero();
		break;
	case BigJasonDirectState::RIGHTWALK:
		this->directState = BigJasonDirectState::RIGHTWALK;
		this->velocity = Vector2D(PLAYER_MOVING_SPEED, 0);
		this->nx = 1;
		break;
	case BigJasonDirectState::LEFTWALK:
		this->directState = BigJasonDirectState::LEFTWALK;
		this->velocity = Vector2D(-PLAYER_MOVING_SPEED, 0);
		this->nx = -1;
		break;
	case BigJasonDirectState::UPWALK:
		this->directState = BigJasonDirectState::UPWALK;
		this->velocity = Vector2D(0, PLAYER_MOVING_SPEED);
		this->nx = 1;
		break;
	case BigJasonDirectState::DOWNWALK:
		this->directState = BigJasonDirectState::DOWNWALK;
		this->velocity = Vector2D(0, -PLAYER_MOVING_SPEED);
		this->nx = 1;
		break;
	default:
		break;
	}
}

void CBigJason::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CBigJason::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
