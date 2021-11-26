#include "SophiaWheel.h"

CSophiaWheel::CSophiaWheel(CGameObject* target)
{
	this->target = target;
}

void CSophiaWheel::Update(DWORD dt)
{
	// update wheel
	this->position += this->velocity * dt;
}

void CSophiaWheel::Render()
{
	// get wheel animation
	auto animation = this->animations.at(0);

}
