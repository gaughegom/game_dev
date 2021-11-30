#include "EnemyOffside.h"

CEnemyOffside::CEnemyOffside()
{
	this->AddAnimation("default", 240); // 240: offside animation id
}

void CEnemyOffside::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyOffside::Render()
{
	animations.at("default")->Render(this->position, 1, 255);
}
