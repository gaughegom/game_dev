#include "SophiaActionState.h"

CSophiaActionState::CSophiaActionState()
{
}

CSophiaActionState::CSophiaActionState(CSophia* target)
{
	this->target = target;
}

void CSophiaActionState::SetTarget(CSophia* target)
{
	this->target = target;
}

void CSophiaActionState::SetIdleState()
{
	this->target->leftWheel = Vector2D(-8.0f, 0.0f);
	this->target->rightWheel = Vector2D(8.0f, 0.0f);
	this->target->body = Vector2D(0.0f, 1.0f);
	this->target->cabin = Vector2D(-3.5f * this->target->GetNx(), 9);
}
