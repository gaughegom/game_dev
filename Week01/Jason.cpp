#include "Jason.h"

CJason::CJason()
{
	// add animation
	this->AddAnimation(C_JASON_HORIZON, ANIMATION_JASON_LEFT);
	this->AddAnimation(C_JASON_UP, ANIMATION_JASON_UP);
	this->AddAnimation(C_JASON_DOWN, ANIMATION_JASON_DOWN);
	// set size
	this->SetSize(24, 32);

	// set state
	this->directState = new CJasonDirectionState(this);
	this->directState->Stay();

	// set position
	this->SetPosition(140, 20);

	// set velocity
	this->SetVelocity(0, 0);
}

void CJason::Update(DWORD dt)
{
	LinearMove(*this, dt);
	this->EdgeCollisionHandler();

	this->ListenKeyEvent();
}

void CJason::Render()
{
	auto animationId = this->directState->MappingStateOfAnimation(this->directState->GetState());
	this->animations.at(animationId)->
		Render(this->position, this->nx);
}

void CJason::ListenKeyEvent()
{
	auto game = CGame::GetInstance();
	// listen key
}

void CJason::EdgeCollisionHandler()
{
	if (this->position.x >=	QUADTREE_WIDTH - this->width) {
		this->position.x = QUADTREE_WIDTH - this->width;
		return;
	}
	if (this->position.x <= 0) {
		this->position.x = 0;
		return;
	}
	if (this->position.y >= QUADTREE_HEIGHT - this->height) {
		this->position.y = QUADTREE_HEIGHT - this->height;
		return;
	}
	if (this->position.y <= -10) {
		this->position.y = -10;
		return;
	}
}

void CJason::SubcribeDirectionState(int directState)
{
	this->directState->SetState(directState);
	switch (directState)
	{
	case JASON_STATE_DIRECTION_FORWARD:
		this->SetVelocity(PLAYER_MOVING_SPEED, 0);
		this->nx = 1;
		this->directState->MoveForward();
		break;
	case JASON_STATE_DIRECTION_BACKWARD:
		this->SetVelocity(-PLAYER_MOVING_SPEED, 0);
		this->nx = -1;
		this->directState->MoveBackward();
		break;
	case JASON_STATE_DIRECTION_UPWARD:
		this->SetVelocity(0, PLAYER_MOVING_SPEED);
		this->directState->MoveUpward();
		break;
	case JASON_STATE_DIRECTION_DOWNWARD:
		this->SetVelocity(0, -PLAYER_MOVING_SPEED);
		this->directState->MoveDownWard();
		break;
	default:
		this->SetVelocity(0, 0);
		this->directState->Stay();
		break;
	}
}
