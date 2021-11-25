#include "EnemyEyelet.h"

CEnemyEyelet::CEnemyEyelet()
{
	// animation
	this->AddAnimation(C_EYELET, ANIMATION_ENEMY_EYELET);
	// position
	this->SetPosition(PLAYER_START_X + 50, PLAYER_START_Y + 20);
	// velocity
	this->SetVelocity(0, 0);
}

void CEnemyEyelet::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyEyelet::Render()
{
	animations.at(C_EYELET)->Render(this->position, 1);
}
