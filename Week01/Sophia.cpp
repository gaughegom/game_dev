#include "Sophia.h"
#include "SophiaStateIdle.h"
#include "SophiaStateMoveForward.h"
#include "SophiaStateMoveBackward.h"
#include "SophiaStateNotMove.h"

CSophia::CSophia()
{
	this->AddAnimation(LEFT_WHEEL, ANIMATION_SOPHIA_LEFT_WHEEL);
	this->AddAnimation(RIGHT_WHEEL, ANIMATION_SOPHIA_RIGHT_WHEEL);
	auto sprites = CSprites::GetInstance();
	this->lpsBody = sprites->Get(SPRITE_SOPHIA_BODY);
	this->lpsCabin = sprites->Get(SPRITE_SOPHIA_CABIN);

	this->wheelState = new CSophiaStateNotMove;
	this->directState = new CSophiaStateIdle;
}

void CSophia::Update(DWORD dt)
{
	LinearMovement(this->position, this->velocity, dt);
	this->directState->Update(dt, this->nx, *this);

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

void CSophia::Render()
{
	this->wheelState->Render(*this);
	animations.at(LEFT_WHEEL)->Render(this->position + this->leftWheel, 1);
	animations.at(RIGHT_WHEEL)->Render(this->position + this->rightWheel, 1);
	lpsBody->Draw(this->position + this->body, this->nx);
	lpsCabin->Draw(this->position + this->cabin, this->nx);
}

int CSophia::GetState()
{
	switch (this->state)
	{
	case SOPHIA_STATE_MOVING_RIGHT:
		return PLAYER_ANIMATION_MOVING_RIGHT;
	case SOPHIA_STATE_MOVING_LEFT:
		return PLAYER_ANIMATION_MOVING_LEFT;
	default:
		switch (this->nx)
		{
		case 1:
			return PLAYER_ANIMATION_IDLE_RIGHT;
		case -1:
			return PLAYER_ANIMATION_IDLE_LEFT;
		}
	}
}

void CSophia::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SOPHIA_STATE_MOVING_RIGHT:
		this->SetVelocity(PLAYER_MOVING_SPEED, 0);
		this->nx = 1;
		this->wheelState = new CSophiaStateMoveForward;
		break;
	case SOPHIA_STATE_MOVING_LEFT:
		this->SetVelocity(-PLAYER_MOVING_SPEED, 0);
		this->nx = -1;
		this->wheelState = new CSophiaStateMoveBackward;
		break;

	case SOPHIA_STATE_IDLE:
		this->SetVelocity(0, 0);
		this->wheelState = new CSophiaStateNotMove;
		break;
	default:
		this->SetVelocity(0, 0);
		this->position.x;
		this->wheelState = new CSophiaStateNotMove;
		break;
	}
}