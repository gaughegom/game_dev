#include "EnemyRobot.h"

CEnemyRobot::CEnemyRobot()
{
	this->AddAnimation(C_ROBOT, ANIMATION_ENEMY_ROBOT);
	this->SetSize(14, 26);
}

void CEnemyRobot::Update(DWORD dt)
{
	this->position.x += this->velocity.x * dt;
	this->position.y += this->velocity.y * dt;
}

void CEnemyRobot::Render()
{
	auto animation = this->animations.at(C_ROBOT);
	animation->Render(this->position, this->nx);
}

int CEnemyRobot::GetState()
{
	return 0;
}

void CEnemyRobot::SetState(int state)
{
	
}
