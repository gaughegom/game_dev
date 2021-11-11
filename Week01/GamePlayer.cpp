#include "GamePlayer.h"
#include "Game.h"

void CGamePlayer::Update(DWORD dt)
{
	CGameObject::Update(dt);

	int backbufferWidth = CGame::Get_instance()->Get_backbuffer_width();
	int backbufferHeight = CGame::Get_instance()->Get_backbuffer_height();

	// simple screen edge collision!!!
	if (this->vx > 0 && this->x >  backbufferWidth - PLAYER_WIDTH) {
		this->x = backbufferWidth - PLAYER_WIDTH;
	}
	if (this->vx < 0 && this->x < 0) {
		this->x = 0;
	}
	if (this->vy > 0 && this->y > backbufferHeight - PLAYER_HEIGHT) {
		this->y = backbufferHeight - PLAYER_HEIGHT;
	}
	if (this->vy < 0 && this->y < 0) {
		this->y = 0;
	}
}

void CGamePlayer::Render()
{
	int animation = CGamePlayer::Get_state();
	animations[animation]->Render(this->x, this->y);
}

int CGamePlayer::Get_state()
{
	if (this->vx == 0) {
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