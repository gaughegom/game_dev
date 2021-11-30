#include "EnemyDrap.h"

CEnemyDrap::CEnemyDrap()
{
	this->AddAnimation("default", 200); // 200: drap animation id
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
	animation->Render(this->position, 1, 255);
}
