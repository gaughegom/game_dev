#include "JasonDirectionState.h"

CJasonDirectionState::CJasonDirectionState()
{
}

CJasonDirectionState::CJasonDirectionState(CJason* target)
{
	this->target = target;
}

void CJasonDirectionState::SetTarget(CJason* target)
{
	this->target = target;
}

void CJasonDirectionState::SetState(JasonDirectState state)
{
	this->state = state;
}

JasonDirectState CJasonDirectionState::GetState()
{
	return this->state;
}

std::string CJasonDirectionState::MappingStateOfAnimation()
{
	switch (this->state)
	{
	case JasonDirectState::LEFTWALK:
		return ANIMATION_JASON_WALK_ID;

	case JasonDirectState::RIGHTWALK:
		return ANIMATION_JASON_WALK_ID;

	case JasonDirectState::STAY:
		return ANIMATION_JASON_STAY_ID;

	case JasonDirectState::JUMP:
		return ANIMATION_JASON_STAY_ID;

	default:
		return ANIMATION_JASON_STAY_ID;
	}
}

void CJasonDirectionState::Stay()
{
	auto targetAnimations = this->target->GetAnimations();
	auto key = MappingStateOfAnimation();

	auto animation = targetAnimations.at(key);
	animation->SetWait(true);
}

void CJasonDirectionState::MoveBackward()
{
	auto targetAnimations = this->target->GetAnimations();
	auto animation = targetAnimations
		.at(MappingStateOfAnimation());

	animation->SetReverse(false);
	animation->SetWait(false);
}

void CJasonDirectionState::MoveForward()
{
	auto targetAnimations = this->target->GetAnimations();
	auto animation = targetAnimations
		.at(MappingStateOfAnimation());

	animation->SetReverse(true);
	animation->SetWait(false);
}

void CJasonDirectionState::Jump()
{
	auto targetAnimations = this->target->GetAnimations();
	auto key = MappingStateOfAnimation();

	auto animation = targetAnimations.at(key);
	animation->SetWait(true);
}
