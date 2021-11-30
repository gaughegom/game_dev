#include "EnemyStuka.h"

CEnemyStuka::CEnemyStuka()
{
	this->AddAnimation("default", 210); // 210: stuka animation id
}

void CEnemyStuka::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyStuka::Render()
{
	animations.at("default")->Render(this->position, 1, 255);
}
