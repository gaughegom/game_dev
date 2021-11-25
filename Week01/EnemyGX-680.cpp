#include "EnemyGX-680.h"

CEnemyGX680::CEnemyGX680()
{
	// add animation
	this->AddAnimation(C_GX680, ANIMATION_ENEMY_GX680);
	// set size
	this->SetSize(18, 18);
	// set postition
	this->SetPosition(PLAYER_START_X + 80, PLAYER_START_Y + 20);
	// set velocity
	this->SetVelocity(0, 0);
}

void CEnemyGX680::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyGX680::Render()
{
	animations.at(C_GX680)->Render(this->position, 1);
}
