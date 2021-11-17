#include "EnemyRobot.h"

void CEnemyRobot::Update(DWORD dt)
{
	this->position.x += this->velocity.x * dt;
	this->position.y += this->velocity.y * dt;
}

void CEnemyRobot::Render()
{
	animations.at(ENEMY_ROBOT_IDLE)->Render(this->position, this->nx);
}

int CEnemyRobot::GetState()
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

void CEnemyRobot::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case NPC_STATE_MOVING_RIGHT:
		this->velocity.x = NPC_MOVING_SPEED;
		this->velocity.y = 0;
		break;
	case NPC_STATE_MOVING_LEFT:
		this->velocity.x = -NPC_MOVING_SPEED;
		this->velocity.y = 0;
		break;
	case NPC_STATE_MOVING_DOWN:
		this->velocity.x = 0;
		this->velocity.y = NPC_MOVING_SPEED;
		break;
	case NPC_STATE_MOVING_UP:
		this->velocity.x = 0;
		this->velocity.y = -NPC_MOVING_SPEED;
		break;
	default:
		break;
	}
}
