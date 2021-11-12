#include "GameNpc.h"

void CGameNpc::Update(DWORD dt)
{
	CGameObject::Update(dt);

	int backbufferWidth = CGame::Get_instance()->Get_backbuffer_width();
	int backbufferHeight = CGame::Get_instance()->Get_backbuffer_height();

	// clock
	//Npc_move_follow_clock(backbufferHeight, backbufferWidth);

	// reverse clock
	Npc_move_reverse_clock(backbufferHeight, backbufferWidth);
}

void CGameNpc::Npc_move_follow_clock(int backbufferWidth, int backbufferHeight)
{
	switch (this->state)
	{
	case NPC_STATE_MOVING_UP:
		if (this->y < 0) {
			CGameObject::Set_y(NPC_START_Y);
			CGameNpc::Set_state(NPC_STATE_MOVING_RIGHT);
		}
		break;
	case NPC_STATE_MOVING_DOWN:
		if (this->y > backbufferHeight - PLAYER_HEIGHT) {
			CGameObject::Set_y(backbufferHeight - PLAYER_HEIGHT);
			CGameNpc::Set_state(NPC_STATE_MOVING_LEFT);
		}
		break;
	case NPC_STATE_MOVING_RIGHT:
		if (this->x > backbufferWidth - PLAYER_WIDTH) {
			CGameObject::Set_x(backbufferWidth - PLAYER_WIDTH);
			CGameNpc::Set_state(NPC_STATE_MOVING_DOWN);
		}
		break;
	case NPC_STATE_MOVING_LEFT:
		if (this->x < 0) {
			CGameObject::Set_x(NPC_START_X);
			CGameNpc::Set_state(NPC_STATE_MOVING_UP);
		}
		break;
	default:
		break;
	}
}

void CGameNpc::Npc_move_reverse_clock(int backbufferHeight, int backbufferWidth)
{
	switch (this->state)
	{
	case NPC_STATE_MOVING_UP:
		if (this->y < 0) {
			CGameObject::Set_y(NPC_START_Y);
			CGameNpc::Set_state(NPC_STATE_MOVING_LEFT);
		}
		break;
	case NPC_STATE_MOVING_DOWN:
		if (this->y > backbufferHeight - PLAYER_HEIGHT) {
			CGameObject::Set_y(backbufferHeight - PLAYER_HEIGHT);
			CGameNpc::Set_state(NPC_STATE_MOVING_RIGHT);
		}
		break;
	case NPC_STATE_MOVING_RIGHT:
		if (this->x > backbufferWidth - PLAYER_WIDTH) {
			CGameObject::Set_x(backbufferWidth - PLAYER_WIDTH);
			CGameNpc::Set_state(NPC_STATE_MOVING_UP);
		}
		break;
	case NPC_STATE_MOVING_LEFT:
		if (this->x < 0) {
			CGameObject::Set_x(NPC_START_X);
			CGameNpc::Set_state(NPC_STATE_MOVING_DOWN);
		}
		break;
	default:
		break;
	}
}

void CGameNpc::Render()
{
	int animation = CGameNpc::Get_state();
	this->animations[animation]->Render(this->x, this->y);
}

int CGameNpc::Get_state()
{
	switch (this->state)
	{
	case NPC_STATE_MOVING_LEFT:
		return NPC_ANIMATION_MOVING_LEFT;
	case NPC_STATE_MOVING_DOWN:
		return NPC_ANIMATION_MOVING_DOWN;
	case NPC_STATE_MOVING_UP:
		return NPC_ANIMATION_MOVING_UP;
	default:
		return NPC_ANIMATION_MOVING_RIGHT;
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
