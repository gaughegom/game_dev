#include "EnemyGX-680.h"

CEnemyGX680::CEnemyGX680()
{
	this->SetSize(18, 18);
	this->SetPosition(PLAYER_START_X + 80, PLAYER_START_Y + 20);
	this->SetVelocity(0, 0);
	this->AddAnimation("default", 230); // 230: gx-680 animation id
}

void CEnemyGX680::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyGX680::Render()
{
	animations.at("default")->Render(this->position, 1);
}
