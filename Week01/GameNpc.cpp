#include "GameNpc.h"

void CGameNpc::Update(DWORD dt)
{
	CGameObject::Update(dt);

	int backbufferWidth = CGame::Get_instance()->Get_backbuffer_width();
	int backbufferHeight = CGame::Get_instance()->Get_backbuffer_height();

	if (this->vy < 0 && this->y < 0) {
		this->y = NPC_START_Y;
		CGameNpc::Set_state(NPC_STATE_MOVING_RIGHT);
	}
	else if (this->vx > 0 && this->x > backbufferWidth - PLAYER_WIDTH) {
		this->x = backbufferWidth - PLAYER_WIDTH;
		CGameNpc::Set_state(NPC_STATE_MOVING_DOWN);
	}
	else if (this->vx < 0 && this->x < 0) {
		this->x = NPC_START_X;
		CGameNpc::Set_state(NPC_STATE_MOVING_UP);
	}
	else if (this->vy > 0 && this->y > backbufferHeight - PLAYER_HEIGHT) {
		this->y = backbufferHeight - PLAYER_HEIGHT;
		CGameNpc::Set_state(NPC_STATE_MOVING_LEFT);
	}
}

void CGameNpc::Render()
{
	int animation = CGameNpc::Get_state();
	this->animations[animation]->Render(this->x, this->y);
}

int CGameNpc::Get_state()
{
	if (this->vx == 0) {
		if (this->vy > 0) {
			return NPC_ANIMATION_MOVING_DOWN;
		}
		else {
			return NPC_ANIMATION_MOVING_UP;
		}
	}
	else if (this->vx > 0) {
		return NPC_ANIMATION_MOVING_RIGHT;
	}
	else {
		return NPC_ANIMATION_MOVING_LEFT;
	}
}

void CGameNpc::Set_state(int state)
{
	CGameObject::Set_state(state);
	switch (state)
	{
	case NPC_STATE_MOVING_RIGHT:
		this->vx = NPC_MOVING_SPEED;
		this->vy = 0;
		break;
	case NPC_STATE_MOVING_LEFT:
		this->vx = -NPC_MOVING_SPEED;
		this->vy = 0;
		break;
	case NPC_STATE_MOVING_DOWN:
		this->vx = 0;
		this->vy = NPC_MOVING_SPEED;
		break;
	case NPC_STATE_MOVING_UP:
		this->vx = 0;
		this->vy = -NPC_MOVING_SPEED;
		break;
	default:
		break;
	}
}
