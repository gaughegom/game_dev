#include "SophiaDirectState.h"

CSophiaDirectState::CSophiaDirectState()
{
}

CSophiaDirectState::CSophiaDirectState(CSophia* target)
{
	this->target = target;
}

void CSophiaDirectState::SetTarget(CSophia* target)
{
	this->target = target;
}

void CSophiaDirectState::Stay()
{
	auto animations = this->target->GetAnimations();
	auto left_wheel = animations.at("left-wheel");
	auto right_wheel = animations.at("right-wheel");

	left_wheel->SetWait(true);
	right_wheel->SetWait(true);
}

void CSophiaDirectState::MoveBackward()
{
	auto animations = this->target->GetAnimations();
	auto left_wheel = animations.at("left-wheel");
	auto right_wheel = animations.at("right-wheel");

	left_wheel->SetReverse(false);
	right_wheel->SetReverse(false);

	left_wheel->SetWait(false);
	right_wheel->SetWait(false);
}

void CSophiaDirectState::MoveForward()
{
	auto animations = this->target->GetAnimations();
	auto left_wheel = animations.at("left-wheel");
	auto right_wheel = animations.at("right-wheel");

	left_wheel->SetReverse(true);
	right_wheel->SetReverse(true);

	left_wheel->SetWait(false);
	right_wheel->SetWait(false);
}

void CSophiaDirectState::SetState(int state)
{
	this->state = state;
}

int CSophiaDirectState::GetState()
{
	return this->state;
}
