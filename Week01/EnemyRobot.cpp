#include "EnemyRobot.h"

CEnemyRobot::CEnemyRobot()
{
	this->AddAnimation(1, 1000);
}

void CEnemyRobot::Update(DWORD dt)
{
	this->position.x += this->velocity.x * dt;
	this->position.y += this->velocity.y * dt;
}

void CEnemyRobot::Render()
{
	auto animation = this->animations.at(1);
	animation->Render(this->position, this->nx);
}

int CEnemyRobot::GetState()
{
	return 0;
}

void CEnemyRobot::SetState(int state)
{
	
}
