#include "EnemyDrap.h"

CEnemyDrap::CEnemyDrap()
{
	// set position
	this->SetPosition(PLAYER_START_X + 20, PLAYER_START_Y + 20);
	this->SetSize(18, 18);
	// add animation
	this->AddAnimation("default", ANIMATION_ENEMY_DRAP);
	// set velocity
	this->SetVelocity(0, 0);
	// set size
}

void CEnemyDrap::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyDrap::Render()
{
	// get id of state
	
	// render
	auto animation = this->animations.at("default");
	animation->SetWait(false);
	animation->Render(this->position, 1);
}
