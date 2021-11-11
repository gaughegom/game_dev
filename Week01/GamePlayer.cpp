#include "GamePlayer.h"

void CGamePlayer::Update(DWORD dt)
{
	CGameObject::Update(dt);

	int backbufferWidth = CGame::Get_instance()->Get_backbuffer_width();
	int backbufferHeight = CGame::Get_instance()->Get_backbuffer_height();

	// simple screen edge collision!!!
	switch (this->state)
	{
	case PLAYER_STATE_MOVING_RIGHT:
		if (this->x > backbufferWidth - PLAYER_WIDTH) {
			this->x = backbufferWidth - PLAYER_WIDTH;
		}
	case PLAYER_STATE_MOVING_LEFT:
		if (this->x < 0) {
			this->x = 0;
		}
	case PLAYER_STATE_MOVING_DOWN:
		if (this->y > backbufferHeight - PLAYER_HEIGHT) {
			this->y = backbufferHeight - PLAYER_HEIGHT;
		}
	case PLAYER_STATE_MOVING_UP:
		if (this->y < 0) {
			this->y = 0;
		}
	default:
		break;
	}
}

void CGamePlayer::Render()
{
	int animation = CGamePlayer::Get_state();
	animations[animation]->Render(this->x, this->y);
}

int CGamePlayer::Get_state()
{
	/*if (this->vx == 0) {
		if (this->vy == 0) {
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
		else if (this->vy > 0) {
			return PLAYER_ANIMATION_MOVING_DOWN;
		}
		else {
			return PLAYER_ANIMATION_MOVING_UP;
		}
	}
	else if (this->vx > 0) {
		return PLAYER_ANIMATION_MOVING_RIGHT;
	}
	else {
		return PLAYER_ANIMATION_MOVING_LEFT;
	}*/
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
		this->vx = PLAYER_MOVING_SPEED;
		this->vy = 0;
		this->nx = 1;
		break;
	case PLAYER_STATE_MOVING_LEFT:
		this->vx = -PLAYER_MOVING_SPEED;
		this->vy = 0;
		this->nx = -1;
		break;
	case PLAYER_STATE_MOVING_UP:
		this->vy = -PLAYER_MOVING_SPEED;
		this->vx = 0;
		this->nx = -2;
		break;
	case PLAYER_STATE_MOVING_DOWN:
		this->vy = PLAYER_MOVING_SPEED;
		this->vx = 0;
		this->nx = 2;
		break;

	case PLAYER_STATE_IDLE:
		this->vx = 0;
		this->vy = 0;
		break;
	}
}