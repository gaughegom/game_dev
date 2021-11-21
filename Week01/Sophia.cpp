#include "Sophia.h"

CSophia::CSophia()
{
	this->directState = new CSophiaDirectState(this);
	this->actionState = new CSophiaActionState(this);

	this->AddAnimation(LEFT_WHEEL, ANIMATION_SOPHIA_LEFT_WHEEL);
	this->AddAnimation(RIGHT_WHEEL, ANIMATION_SOPHIA_RIGHT_WHEEL);
	auto sprites = CSprites::GetInstance();
	this->lpsBody = sprites->Get(SPRITE_SOPHIA_BODY);

	this->directState->Stay();
	this->actionState->IdleState();
}

void CSophia::Update(DWORD dt)
{
	LinearMovement(this->position, this->velocity, dt);

	int backbufferWidth = CGame::GetInstance()->GetBackbufferWidth();
	this->EdgeCollisionHandler(CGame::GetInstance()->GetBackbufferWidth());

}

void CSophia::EdgeCollisionHandler(int width)
{
	switch (this->state)
	{
	case SOPHIA_STATE_DIRECTION_FORWARD:
		if (this->position.x > width * 10 - PLAYER_WIDTH) {
			this->SetX(width * 10 - PLAYER_WIDTH);
		}
	case SOPHIA_STATE_DIRECTION_BACKWARD:
		if (this->position.x < 0) {
			this->SetX(0);
		}
	default:
		break;
	}
}

void CSophia::Render()
{
	animations.at(LEFT_WHEEL)->RenderGame(this->position + this->leftWheel, 1);
	animations.at(RIGHT_WHEEL)->RenderGame(this->position + this->rightWheel, 1);
	this->lpsBody->Draw(this->position + this->body, this->nx);
	this->lpsCabin->Draw(this->position + this->cabin, this->nx);
	this->lpsGun->Draw(this->position + this->gun, this->nx);
}

void CSophia::ObserveDirectState(int directState)
{
	this->directState->SetState(directState);
	switch (directState)
	{
	case SOPHIA_STATE_DIRECTION_STAY:
		this->SetVelocity(0, 0);
		this->directState->Stay();
		this->ObserveActionState(this->actionState->GetState());
		break;
	case SOPHIA_STATE_DIRECTION_BACKWARD:
		this->SetVelocity(-PLAYER_MOVING_SPEED, 0);
		this->nx = -1;
		this->directState->MoveBackward();
		this->ObserveActionState(this->actionState->GetState());
		break;
	case SOPHIA_STATE_DIRECTION_FORWARD:
		this->SetVelocity(PLAYER_MOVING_SPEED, 0);
		this->nx = 1;
		this->directState->MoveForward();
		this->ObserveActionState(this->actionState->GetState());
		break;
	default:
		this->SetVelocity(0, 0);
		this->directState->Stay();
		this->ObserveActionState(this->actionState->GetState());
		break;
	}
}

void CSophia::ObserveActionState(int actionState)
{
	this->actionState->SetState(actionState);
	switch (actionState)
	{
	case SOPHIA_STATE_ACTION_IDLE:
		this->actionState->IdleState();
		break;
	case SOPHIA_STATE_ACTION_TILE_45:
		this->actionState->Tilt45State();
		break;
	case SOPHIA_STATE_ACTION_UP_90:
		this->actionState->Up90State();
		break;
	default:
		this->actionState->IdleState();
		break;
	}
}