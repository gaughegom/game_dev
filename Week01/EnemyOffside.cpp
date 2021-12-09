#include "EnemyOffside.h"

#define ANIMATION_DEFAULT_ID	"df"

CEnemyOffside::CEnemyOffside()
{
	this->AddAnimation(ANIMATION_DEFAULT_ID, "aniEOffside"); // 240: offside animation id
}

void CEnemyOffside::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyOffside::Render()
{
	animations.at(ANIMATION_DEFAULT_ID)->Render(this->position, 1, DRAW_COLOR_DEFAULT);
}
