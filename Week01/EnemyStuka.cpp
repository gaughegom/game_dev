#include "EnemyStuka.h"

CEnemyStuka::CEnemyStuka()
{
	this->AddAnimation(C_STUKA, ANIMATION_ENEMY_STUKA);
	this->SetSize(18, 18);
	this->SetPosition(PLAYER_START_X + 110, PLAYER_START_Y + 20);
	this->SetVelocity(0, 0);
}

void CEnemyStuka::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyStuka::Render()
{
	animations.at(C_STUKA)->Render(this->position, 1);
}
