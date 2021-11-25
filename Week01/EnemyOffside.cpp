#include "EnemyOffside.h"

CEnemyOffside::CEnemyOffside()
{
	this->AddAnimation(CA_OFFSIDE, ANIMATION_ENEMY_OFFSIDE);
	this->SetSize(18, 18);
	this->SetPosition(PLAYER_START_X + 140, PLAYER_START_Y + 20);
	this->SetVelocity(0, 0);
}

void CEnemyOffside::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyOffside::Render()
{
	animations.at(CA_OFFSIDE)->Render(this->position, 1);
}
