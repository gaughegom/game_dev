#include "BigJason.h"
#include "Player.h"
#include "Gate.h"
#include "BigJasonBullet.h"
#include "EnemyGX-680.h"
#include "EnemyGX-680S.h"

#define BOXSIZE_HORIZON				Vector2D(24.0f, 32.0f)
#define BOXSIZE_VERTICAL			Vector2D(20.0f, 32.0f)

constexpr auto AnimationHorizontalWalkId	= "walk-horizon";
constexpr auto AnimationUpWalkId			= "walk-up";
constexpr auto AnimationDownWalkId			= "walk-down";
constexpr auto SpriteHorizontalStayId		= "stay-horizon";
constexpr auto SpriteUpStayId				= "stay-up";
constexpr auto SpriteDownStayId				= "stay-down";

CBigJason::CBigJason()
{
	// init aniamtion, sprite
	this->AddAnimation(AnimationHorizontalWalkId, "aniBJHorizon");
	this->AddAnimation(AnimationUpWalkId, "aniBJUpward");
	this->AddAnimation(AnimationDownWalkId, "aniBJDownward");
	this->AddSprite(SpriteHorizontalStayId, "sprBJHorizon01");
	this->AddSprite(SpriteUpStayId, "sprBJUpward01");
	this->AddSprite(SpriteDownStayId, "sprBJDownward01");

	// velocity
	this->directState = BigJasonDirectState::STAY;
	this->currentSpriteState = SpriteDownStayId;
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
	DebugOut(L"big jason hp: %f\n", this->hp);

	if (CPlayer::GetInstance()->GetSelectId() == PlayerCharacterId::BIGJASON) {
		this->ListenKeyEvent();
	}

	this->UpdateColliders();
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

	if (input->OnKeyDown(SHOTTING_KEYCODE)) {
		this->Shooting();
	}
}

void CBigJason::UpdateColliders()
{
	auto collider = this->colliders.at(0);

	switch (this->directState)
	{
	case BigJasonDirectState::LEFTWALK:
	case BigJasonDirectState::RIGHTWALK:
		this->colliders.at(0)->SetBoxSize(BOXSIZE_HORIZON);
		break;

	case BigJasonDirectState::DOWNWALK:
	case BigJasonDirectState::UPWALK:
		this->colliders.at(0)->SetBoxSize(BOXSIZE_VERTICAL);
		break;

	default:
		break;
	}
}

std::string CBigJason::MappingStateOfAnimation()
{
	switch (this->directState)
	{
	case BigJasonDirectState::LEFTWALK:
		this->currentSpriteState = SpriteHorizontalStayId;
		return AnimationHorizontalWalkId;

	case BigJasonDirectState::RIGHTWALK:
		this->currentSpriteState = SpriteHorizontalStayId;
		return AnimationHorizontalWalkId;

	case BigJasonDirectState::UPWALK:
		this->currentSpriteState = SpriteUpStayId;
		return AnimationUpWalkId;

	case BigJasonDirectState::DOWNWALK:
		this->currentSpriteState = SpriteDownStayId;
		return AnimationDownWalkId;
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
		this->velocity = Vector2D(PlayerMovingSpeed, 0);
		this->nx = 1;
		break;
	case BigJasonDirectState::LEFTWALK:
		this->directState = BigJasonDirectState::LEFTWALK;
		this->velocity = Vector2D(-PlayerMovingSpeed, 0);
		this->nx = -1;
		break;
	case BigJasonDirectState::UPWALK:
		this->directState = BigJasonDirectState::UPWALK;
		this->velocity = Vector2D(0, PlayerMovingSpeed);
		this->nx = 1;
		break;
	case BigJasonDirectState::DOWNWALK:
		this->directState = BigJasonDirectState::DOWNWALK;
		this->velocity = Vector2D(0, -PlayerMovingSpeed);
		this->nx = 1;
		break;
	default:
		break;
	}
}

void CBigJason::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CGate*>(coEvent->object)) {
		CGate* coGate = (CGate*)coEvent->object;
		DebugOut(L"next to another scene %d\n", coGate->GetNextScene());
		CGame::GetInstance()->SwitchScene(coGate->GetNextScene());
	}
	else {
		this->OnCollisionWithEnemy(coEvent);
	}
}

void CBigJason::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CBigJason::Shooting()
{
	CGame* game = CGame::GetInstance();
	LPGAMEOBJECT newBullet = nullptr;
	switch (this->directState)
	{
	case BigJasonDirectState::LEFTWALK:
		newBullet = new CBigJasonBullet(BigJasonBulletDirection::LEFT);
		break;

	case BigJasonDirectState::RIGHTWALK:
		newBullet = new CBigJasonBullet(BigJasonBulletDirection::RIGHT);
		break;

	case BigJasonDirectState::UPWALK:
		newBullet = new CBigJasonBullet(BigJasonBulletDirection::UP);
		break;

	case BigJasonDirectState::DOWNWALK:
		newBullet = new CBigJasonBullet(BigJasonBulletDirection::DOWN);
		break;

	case BigJasonDirectState::STAY:
		if (this->currentSpriteState == SpriteHorizontalStayId) {
			switch (this->nx)
			{
			case 1:
				newBullet = new CBigJasonBullet(BigJasonBulletDirection::RIGHT);
				break;
			case -1:
				newBullet = new CBigJasonBullet(BigJasonBulletDirection::LEFT);
				break;
			default:
				break;
			}
		}
		else if (this->currentSpriteState == SpriteUpStayId) {
			newBullet = new CBigJasonBullet(BigJasonBulletDirection::UP);
		}
		else if (this->currentSpriteState == SpriteDownStayId) {
			newBullet = new CBigJasonBullet(BigJasonBulletDirection::DOWN);
		}

	default:
		break;
	}

	newBullet->SetPosition(this->position);
	game->NewGameObject(newBullet);
}

void CBigJason::OnCollisionWithEnemy(LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CEnemyGX680*>(coEvent->object)
		|| dynamic_cast<CEnemyGX680S*>(coEvent->object)) {
		this->TakeDamage(coEvent->object->GetDamage());

		STriggerTag tag = STriggerTag(coEvent->object);
		this->AddTriggerTag(coEvent->object);
		coEvent->object->AddTriggerTag(this);
	}
}
