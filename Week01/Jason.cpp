#include "Jason.h"

CJason::CJason()
{	
	this->AddAnimation("stay", 30);
	this->AddAnimation("walk", 31);

	this->directState = new CJasonDirectionState(this);
	this->directState->SetState(JasonDirectState::STAY);

	//
	auto collider = new CCollider2D;
	collider->SetGameObject(this);
	collider->SetOffset(VectorZero());
	collider->SetBoxSize(Vector2D(8.0f, 16.0f));
	collider->SetDynamic(true);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CJason::Update(DWORD dt)
{
	//LinearMoveInGravity(this, dt);
	LinearMove(this, dt);

	if (this->IsSelected()) {
		this->ListenKeyEvent();
	}
}

void CJason::Render()
{
	auto key = this->directState->MappingStateOfAnimation(
		this->directState->GetState());
		
	this->animations.at(key)->
		Render(this->position, -this->nx, 255);

	// draw center point
	auto debugPosSprite = CSprites::GetInstance()->Get(2000);
	Vector2D debugPos = Vector2D(this->position.x - 8, this->position.y);
	debugPosSprite->Draw(debugPos, this->nx, 255);
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

void CJason::SubcribeDirectionState(JasonDirectState directState)
{
	this->directState->SetState(directState);
	switch (directState)
	{
	case JasonDirectState::RIGHTWALK:
		this->SetVelocity(Vector2D(PLAYER_MOVING_SPEED, 0));
		this->nx = 1;
		this->directState->MoveForward();
		break;

	case JasonDirectState::LEFTWALK:
		this->SetVelocity(Vector2D(-PLAYER_MOVING_SPEED, 0));
		this->nx = -1;
		this->directState->MoveBackward();
		break;

	default:
		this->SetVelocity(VectorZero());
		this->directState->Stay();
		break;
	}
}
