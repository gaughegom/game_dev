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

void CSophiaDirectState::SetNotMove()
{
	auto animations = this->target->GetAnimations();
	auto left_wheel = animations.at(LEFT_WHEEL);
	auto right_wheel = animations.at(RIGHT_WHEEL);

	left_wheel->SetWait(true);
	right_wheel->SetWait(true);
}

void CSophiaDirectState::SetMoveBackward()
{
	auto animations = this->target->GetAnimations();
	auto left_wheel = animations.at(LEFT_WHEEL);
	auto right_wheel = animations.at(RIGHT_WHEEL);

	left_wheel->SetReverse(false);
	right_wheel->SetReverse(false);

	left_wheel->SetWait(false);
	right_wheel->SetWait(false);
}

void CSophiaDirectState::SetMoveForward()
{
	auto animations = this->target->GetAnimations();
	auto left_wheel = animations.at(LEFT_WHEEL);
	auto right_wheel = animations.at(RIGHT_WHEEL);

	left_wheel->SetReverse(true);
	right_wheel->SetReverse(true);

	left_wheel->SetWait(false);
	right_wheel->SetWait(false);
}
