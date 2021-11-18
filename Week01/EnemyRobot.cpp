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
	return 0;
}

void CEnemyRobot::SetState(int state)
{
	
}
