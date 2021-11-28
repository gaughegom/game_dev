#include "EnemyStuka.h"

CEnemyStuka::CEnemyStuka()
{
	this->SetSize(18, 18);
	this->SetPosition(PLAYER_START_X + 110, PLAYER_START_Y + 20);
	this->SetVelocity(0, 0);
	this->AddAnimation("default", 210); // 210: stuka animation id
}

void CEnemyStuka::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyStuka::Render()
{
	animations.at("default")->Render(this->position, 1);
}
