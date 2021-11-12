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
		if (this->position.x > backbufferWidth - PLAYER_WIDTH) {
			CGameObject::Set_x(backbufferWidth - PLAYER_WIDTH);
		}
	case PLAYER_STATE_MOVING_LEFT:
		if (this->position.x < 0) {
			CGameObject::Set_x(0);
		}
	case PLAYER_STATE_MOVING_DOWN:
		if (this->position.y > backbufferHeight - PLAYER_HEIGHT) {
			CGameObject::Set_y(backbufferHeight - PLAYER_HEIGHT);
		}
	case PLAYER_STATE_MOVING_UP:
		if (this->position.y < 0) {
			CGameObject::Set_y(0);
		}
	default:
		break;
	}
}

void CGamePlayer::Render()
{
	int animation = CGamePlayer::Get_state();
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
		this->velocity.x = PLAYER_MOVING_SPEED;
		this->velocity.y = 0;
		this->nx = 1;
		break;
	case PLAYER_STATE_MOVING_LEFT:
		this->velocity.x = -PLAYER_MOVING_SPEED;
		this->velocity.y = 0;
		this->nx = -1;
		break;
	case PLAYER_STATE_MOVING_UP:
		this->velocity.x = 0;
		this->velocity.y = -PLAYER_MOVING_SPEED;
		this->nx = -2;
		break;
	case PLAYER_STATE_MOVING_DOWN:
		this->velocity.x = 0;
		this->velocity.y = PLAYER_MOVING_SPEED;
		this->nx = 2;
		break;

	case PLAYER_STATE_IDLE:
		this->velocity.x = 0;
		this->velocity.y = 0;
		break;
	}
}