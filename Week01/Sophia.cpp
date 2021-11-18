#include "Sophia.h"

CSophia::CSophia()
{
	this->vt2LeftWheel = this->position - Vector2D(8, 0);
	this->vt2RightWheel = this->position + Vector2D(8, 0);
	this->lpsBody = CSprites::GetInstance()->Get(10020);
	this->lpsCabin = CSprites::GetInstance()->Get(10030);
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
	/*int animation = this->GetState();
	animations[animation]->Render(this->position, this->nx);*/
	
	animations.at(SOPHIA_LEFT_WHEEL_ANIMATION)->Render(
		this->position + this->vt2LeftWheel,
		this->nx);
	animations.at(SOPHIA_RIGHT_WHEEL_ANIMATION)->Render(
		this->position + this->vt2RightWheel,
		this->nx);
	this->lpsBody->Draw(this->position + Vector2D(0, 3), this->nx);
	this->lpsCabin->Draw(this->position + Vector2D(0, 11), this->nx);
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
		break;
	case SOPHIA_STATE_MOVING_LEFT:
		this->SetVelocity(-PLAYER_MOVING_SPEED, 0);
		this->nx = -1;
		break;

	case SOPHIA_STATE_IDLE:
		this->SetVelocity(0, 0);
		break;
	default:
		this->SetVelocity(0, 0);
		this->position.x;
		break;
	}
}