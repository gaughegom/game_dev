#include "Sophia.h"

CSophia::CSophia()
{
	this->directState = new CSophiaDirectState(this);
	this->actionState = new CSophiaActionState(this);

	this->AddAnimation(LEFT_WHEEL, ANIMATION_SOPHIA_LEFT_WHEEL);
	this->AddAnimation(RIGHT_WHEEL, ANIMATION_SOPHIA_RIGHT_WHEEL);
	auto sprites = CSprites::GetInstance();
	this->lpsBody = sprites->Get(SPRITE_SOPHIA_BODY);
	this->lpsCabin = sprites->Get(SPRITE_SOPHIA_CABIN);

	this->directState->SetNotMove();
	this->actionState->SetIdleState();
}

void CSophia::UpdateGame(DWORD dt)
{
	LinearMovement(this->position, this->velocity, dt);

	int backbufferWidth = CGame::GetInstance()->GetBackbufferWidth();
	this->EdgeCollisionHandler(CGame::GetInstance()->GetBackbufferWidth());
}

void CSophia::EdgeCollisionHandler(int width)
{
	switch (this->state)
	{
	case SOPHIA_STATE_MOVING_RIGHT:
		if (this->position.x > width * 10 - PLAYER_WIDTH) {
			this->SetX(width * 10 - PLAYER_WIDTH);
		}
	case SOPHIA_STATE_MOVING_LEFT:
		if (this->position.x < 0) {
			this->SetX(0);
		}
	default:
		break;
	}
}

void CSophia::RenderGame()
{
	animations.at(LEFT_WHEEL)->RenderGame(this->position + this->leftWheel, 1);
	animations.at(RIGHT_WHEEL)->RenderGame(this->position + this->rightWheel, 1);
	lpsBody->Draw(this->position + this->body, this->nx);
	lpsCabin->Draw(this->position + this->cabin, this->nx);
}

int CSophia::GetState()
{
	return 0; // Not use temporarily
}

void CSophia::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SOPHIA_STATE_MOVING_RIGHT:
		this->SetVelocity(PLAYER_MOVING_SPEED, 0);
		this->nx = 1;
		this->directState->SetMoveForward();
		this->actionState->SetIdleState(); // Build upward later
		break;
	case SOPHIA_STATE_MOVING_LEFT:
		this->SetVelocity(-PLAYER_MOVING_SPEED, 0);
		this->nx = -1;
		this->directState->SetMoveBackward();
		this->actionState->SetIdleState();
		break;

	case SOPHIA_STATE_IDLE:
		this->SetVelocity(0, 0);
		this->directState->SetNotMove();
		this->actionState->SetIdleState();
		break;
	default:
		this->SetVelocity(0, 0);
		this->position.x;
		this->directState->SetNotMove();
		this->actionState->SetIdleState();
		break;
	}
}