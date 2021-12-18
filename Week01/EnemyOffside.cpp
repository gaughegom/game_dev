#include "EnemyOffside.h"

#define AnimationDefaultId	"df"

CEnemyOffside::CEnemyOffside()
{
	this->AddAnimation(AnimationDefaultId, "aniEOffside"); // 240: offside animation id
}

void CEnemyOffside::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyOffside::Render()
{
	animations.at(AnimationDefaultId)->Render(this->position, 1, DrawArgbColorDefault());
}
