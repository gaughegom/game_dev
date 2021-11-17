#include "SophiaWheel.h"

void CSophiaWheel::Update(DWORD dt)
{
	LinearMovement(this->position, this->velocity, dt);
}

void CSophiaWheel::Render()
{

}
