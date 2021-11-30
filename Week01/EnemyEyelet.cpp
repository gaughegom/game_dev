#include "EnemyEyelet.h"

CEnemyEyelet::CEnemyEyelet()
{
	this->AddAnimation("default", 220); // eyelet animation id
}

void CEnemyEyelet::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyEyelet::Render()
{
	animations.at("default")->Render(this->position, 1, 255);
}
