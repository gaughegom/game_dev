#include "GamePlayer.h"

void CGamePlayer::Update(DWORD dt)
{
	Move_rectilinear(this->position, this->velocity, dt);

	/*int backbufferWidth = CGame::Get_instance()->Get_backbuffer_width();
	int backbufferHeight = CGame::Get_instance()->Get_backbuffer_height();*/

	// simple screen edge collision!!!
	//EdgeCollisionHandler(backbufferWidth, backbufferHeight);
}

void CGamePlayer::EdgeCollisionHandler(int backbufferWidth, int backbufferHeight)
{
	switch (this->state)
	{
	case PLAYER_STATE_MOVING_RIGHT:
		if (this->position.x > backbufferWidth - PLAYER_WIDTH) {
			this->Set_x(backbufferWidth - PLAYER_WIDTH);
		}
	case PLAYER_STATE_MOVING_LEFT:
		if (this->position.x < 0) {
			this->Set_x(0);
		}
	case PLAYER_STATE_MOVING_DOWN:
		if (this->position.y > backbufferHeight - PLAYER_HEIGHT) {
			this->Set_y(backbufferHeight - PLAYER_HEIGHT);
		}
	case PLAYER_STATE_MOVING_UP:
		if (this->position.y < 0) {
			this->Set_y(0);
		}
	default:
		break;
	}
}

void CGamePlayer::Render()
{
	int animation = this->Get_state();
	animations[animation]->Render(this->position.x, this->position.y);
}

int CGamePlayer::Get_state()
{
	switch (this->state)
	{
	case PLAYER_STATE_MOVING_RIGHT:
		return PLAYER_ANIMATION_MOVING_RIGHT;
	case PLAYER_STATE_MOVING_LEFT:
		return PLAYER_ANIMATION_MOVING_LEFT;
	case PLAYER_STATE_MOVING_DOWN:
		return PLAYER_ANIMATION_MOVING_DOWN;
	case PLAYER_STATE_MOVING_UP:
		return PLAYER_ANIMATION_MOVING_UP;
	default:
		switch (this->nx)
		{
		case 1:
			return PLAYER_ANIMATION_IDLE_RIGHT;
		case -1:
			return PLAYER_ANIMATION_IDLE_LEFT;
		case 2:
			return PLAYER_ANIMAION_IDLE_DOWN;
		case -2:
			return PLAYER_ANIMATION_IDLE_UP;
		}
	}
}

void CGamePlayer::Set_state(int state)
{
	CGameObject::Set_state(state);
	switch (state)
	{
	case PLAYER_STATE_MOVING_RIGHT:
		//this->velocity.Set(PLAYER_MOVING_SPEED, 0);
		this->Set_velocity(PLAYER_MOVING_SPEED, 0);
		this->nx = 1;
		break;
	case PLAYER_STATE_MOVING_LEFT:
		this->Set_velocity(-PLAYER_MOVING_SPEED, 0);
		this->nx = -1;
		break;
	case PLAYER_STATE_MOVING_UP:
		this->Set_velocity(0, -PLAYER_MOVING_SPEED);
		this->nx = -2;
		break;
	case PLAYER_STATE_MOVING_DOWN:
		this->Set_velocity(0, PLAYER_MOVING_SPEED);
		this->nx = 2;
		break;

	case PLAYER_STATE_IDLE:
		this->Set_velocity(0, 0);
		break;
	default:
		this->Set_velocity(0, 0);
		this->position.x;
		break;
	}
}