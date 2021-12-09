#include "EnemyGX-680.h"

#define ANIMATION_DEFAULT_ID "df"

CEnemyGX680::CEnemyGX680()
{
	this->AddAnimation(ANIMATION_DEFAULT_ID, "aniEGX680"); // 230: gx-680 animation id
}

void CEnemyGX680::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyGX680::Render()
{
	animations.at(ANIMATION_DEFAULT_ID)->Render(this->position, 1, DRAW_COLOR_DEFAULT);
}
