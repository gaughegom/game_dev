#include "EnemyDrap.h"

#define ANIMATION_DEFAULT_ID	"df"

CEnemyDrap::CEnemyDrap()
{
	this->AddAnimation(ANIMATION_DEFAULT_ID, "aniEDrap"); // 200: drap animation id
}

void CEnemyDrap::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyDrap::Render()
{
	// get id of state

	// render
	auto animation = this->animations.at(ANIMATION_DEFAULT_ID);
	animation->SetWait(false);
	animation->Render(this->position, 1, DRAW_COLOR_DEFAULT);
}
