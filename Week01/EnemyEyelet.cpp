#include "EnemyEyelet.h"

CEnemyEyelet::CEnemyEyelet()
{
	this->SetPosition(PLAYER_START_X + 50, PLAYER_START_Y + 20);
	this->SetSize(18, 18);
	this->SetVelocity(0, 0);
	this->AddAnimation("default", 220); // eyelet animation id
}

void CEnemyEyelet::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyEyelet::Render()
{
	animations.at("default")->Render(this->position, 1);
}
