#include "EnemyGX-680.h"

CEnemyGX680::CEnemyGX680()
{
	this->AddAnimation("default", 230); // 230: gx-680 animation id
}

void CEnemyGX680::Update(DWORD dt)
{
	this->position += this->velocity * dt;
}

void CEnemyGX680::Render()
{
	animations.at("default")->Render(this->position, 1, DRAW_COLOR_DEFAULT);
}
