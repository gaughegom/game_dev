#include "Jason.h"

CJason::CJason()
{
	// add animation
	this->AddAnimation("stay", 30);
	this->AddAnimation("walk", 31);
	// set size
	this->SetSize(8, 16);

	// set state
	this->directState = new CJasonDirectionState(this);
	this->directState->SetState(JasonDirectState::STAY);

	// set position
	this->SetPosition(140, 70);

	// set velocity
	this->SetVelocity(0, 0);
}

void CJason::Update(DWORD dt)
{
	LinearMoveInGravity(this, dt);
	this->EdgeCollisionHandler();

	if (this->IsSelected()) {
		this->ListenKeyEvent();
	}
}

void CJason::Render()
{
	auto key = this->directState->MappingStateOfAnimation(
		this->directState->GetState());
		
	this->animations.at(key)->
		Render(this->position, this->nx);

	auto debugPosSprite = CSprites::GetInstance()->Get(2000);
	Vector2D debugPos = Vector2D(this->position.x - 8, this->position.y);
	debugPosSprite->Draw(debugPos, this->nx);
}

void CJason::ListenKeyEvent()
{
	auto input = CInputHandler::GetInstance();

	// map direct state
	if (input->IsKeyDown(DIK_RIGHT)) {
		this->directState->SetState(JasonDirectState::RIGHTWALK);
	}
	else if (input->IsKeyDown(DIK_LEFT)) {
		this->directState->SetState(JasonDirectState::LEFTWALK);
	}
	else {
		this->directState->SetState(JasonDirectState::STAY);
	}

	// subcribe direct state
	this->SubcribeDirectionState(this->directState->GetState());
}

void CJason::EdgeCollisionHandler()
{
	auto directState = this->directState->GetState();
	switch (directState)
	{
	case JasonDirectState::RIGHTWALK:
		if (this->position.x >= QUADTREE_WIDTH - this->width) {
			this->position.x = QUADTREE_WIDTH - this->width;
		}
		break;
	case JasonDirectState::LEFTWALK:
		if (this->position.x <= 0) {
			this->position.x = 0;
		}
		break;

	default:
		break;
	}
	if (this->position.y - this->height / 2 <= GAME_GROUND) {
		this->position.y = GAME_GROUND + this->height / 2;
	}
}

void CJason::SubcribeDirectionState(JasonDirectState directState)
{
	this->directState->SetState(directState);
	switch (directState)
	{
	case JasonDirectState::RIGHTWALK:
		this->SetVelocity(PLAYER_MOVING_SPEED, 0);
		this->nx = 1;
		this->directState->MoveForward();
		break;

	case JasonDirectState::LEFTWALK:
		this->SetVelocity(-PLAYER_MOVING_SPEED, 0);
		this->nx = -1;
		this->directState->MoveBackward();
		break;

	default:
		this->SetVelocity(0, 0);
		this->directState->Stay();
		break;
	}
}
