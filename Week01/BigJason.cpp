#include "BigJason.h"
#include "Player.h"
#include "Gate.h"
#include "BigJasonBullet.h"
#include "ItemHealth.h"
#include "ThornyBrick.h"

#define BOXSIZE_HORIZON				Vector2D(21.0f, 8.0f)
#define BOXSIZE_VERTICAL			Vector2D(17.0f, 8.0f)

constexpr auto AnimationHorizontalWalkId	= "walk-horizon";
constexpr auto AnimationUpWalkId			= "walk-up";
constexpr auto AnimationDownWalkId			= "walk-down";
constexpr auto SpriteHorizontalStayId		= "stay-horizon";
constexpr auto SpriteUpStayId				= "stay-up";
constexpr auto SpriteDownStayId				= "stay-down";
constexpr auto DelayShootingTime = 220;

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
		Vector2D(0, -12.0f), BOXSIZE_VERTICAL);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CBigJason::Shooting()
{
	CGame* game = CGame::GetInstance();
	LPGAMEOBJECT bullet = nullptr;
	Vector2D bulletPosition;
	switch (this->directState)
	{
	case BigJasonDirectState::LEFTWALK:
		bullet = new CBigJasonBullet(BigJasonBulletDirection::LEFT);
		bulletPosition = Vector2D(this->position.x, this->position.y - 1.0f);
		break;

	case BigJasonDirectState::RIGHTWALK:
		bullet = new CBigJasonBullet(BigJasonBulletDirection::RIGHT);
		bulletPosition = Vector2D(this->position.x, this->position.y - 1.0f);
		break;

	case BigJasonDirectState::UPWALK:
		bullet = new CBigJasonBullet(BigJasonBulletDirection::UP);
		bulletPosition = Vector2D(this->position.x, this->position.y - 12.0f);
		break;

	case BigJasonDirectState::DOWNWALK:
		bullet = new CBigJasonBullet(BigJasonBulletDirection::DOWN);
		bulletPosition = Vector2D(this->position.x + 4.0f, this->position.y - 12.0f);
		break;

	case BigJasonDirectState::STAY:
		if (this->currentSpriteState == SpriteHorizontalStayId) {
			switch (this->nx)
			{
			case 1:
				bullet = new CBigJasonBullet(BigJasonBulletDirection::RIGHT);
				bulletPosition = Vector2D(this->position.x, this->position.y - 1.0f);
				break;

			case -1:
				bullet = new CBigJasonBullet(BigJasonBulletDirection::LEFT);
				bulletPosition = Vector2D(this->position.x, this->position.y - 1.0f);
				break;

			default:
				break;
			}
		}
		else if (this->currentSpriteState == SpriteUpStayId) {
			bullet = new CBigJasonBullet(BigJasonBulletDirection::UP);
			bulletPosition = Vector2D(this->position.x, this->position.y - 12.0f);
		}
		else if (this->currentSpriteState == SpriteDownStayId) {
			bullet = new CBigJasonBullet(BigJasonBulletDirection::DOWN);
			bulletPosition = Vector2D(this->position.x + 4.0f, this->position.y - 12.0f);
		}

	default:
		break;
	}

	bullet->SetPosition(bulletPosition);
	game->PushToQueueObject(bullet);
	this->prevShootingTime = GetTickCount64();
}

void CBigJason::Update(DWORD dt)
{
	// TODO: update collider

	// TODO: Debug only
	if (this->prevHp != this->hp) {
		DebugOut(L"big jason hp: %f\n", this->hp);
		this->prevHp = this->hp;
	}

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
		this->sprites.at(this->currentSpriteState)->Draw(this->position, -this->nx, color, DrawLayer02);
	}
	else {
		std::string aniKey = this->MappingStateOfAnimation();
		this->animations.at(aniKey)->Render(this->position, -this->nx, color, DrawLayer02);
	}
}

void CBigJason::ListenKeyEvent()
{
	auto input = CInputHandler::GetInstance();

	bool staying = true;
	// map direct state
	if (input->IsKeyDown(DIK_RIGHT)) {
		this->SubcribeDirectState(BigJasonDirectState::RIGHTWALK);
		staying = false;
	}
	else if (input->IsKeyDown(DIK_LEFT)) {
		this->SubcribeDirectState(BigJasonDirectState::LEFTWALK);
		staying = false;
	}

	if (input->IsKeyDown(DIK_UP)) {
		this->SubcribeDirectState(BigJasonDirectState::UPWALK);
		staying = false;
	}
	else if (input->IsKeyDown(DIK_DOWN)) {
		this->SubcribeDirectState(BigJasonDirectState::DOWNWALK);
		staying = false;
	}
	
	if (staying) {
		this->SubcribeDirectState(BigJasonDirectState::STAY);
	}

	if (input->IsKeyDown(SHOTTING_KEYCODE)
		&& GetTickCount64() - this->prevShootingTime > DelayShootingTime) {
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
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CBrick*>(other)) {
		if (!this->ground && coEvent->ny == 1) {
			this->ground = true;
		}
	}
	else if (dynamic_cast<CGate*>(other)) {
		CGate* gate = (CGate*)other;
		CGame::GetInstance()->SwitchScene(gate->GetNextScene());
	}
	else if (dynamic_cast<CItemBase*>(other)) {
		this->OnCollisionWithItem((CItemBase*)(other));
	}
	else if (dynamic_cast<CEnemyBase*>(other)) {
		this->OnCollisionWithEnemy((CEnemyBase*)other);
	} 
	else if (dynamic_cast<CThornyBrick*>(other) && !this->IsInThorny()) {
		this->SetInThorny(true);
	}
}

void CBigJason::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CBigJason::OnCollisionWithEnemy(CEnemyBase* const& other)
{
	other->TakeDamage(this->damage);
	this->TakeDamage(other->GetDamage());

	STriggerTag tag = STriggerTag(other);
	other->AddTriggerTag(this);
	this->AddTriggerTag(other);
}

void CBigJason::OnCollisionWithItem(CItemBase* const& other) 
{
	if (dynamic_cast<CItemHealth*>(other)) {
		CItemHealth* item = (CItemHealth*)other;
		this->hp += item->GetRecoverHealth();
	}

	other->OnUse();
	// reset hp
	if (this->hp > 100) {
		this->hp = 100;
	}
}
