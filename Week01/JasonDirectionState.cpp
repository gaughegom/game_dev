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

void CJasonDirectionState::SetState(int state)
{
	this->state = state;
}

int CJasonDirectionState::GetState()
{
	return this->state;
}

int CJasonDirectionState::MappingStateOfAnimation(int state)
{
	switch (state)
	{
	case JASON_STATE_DIRECTION_DOWNWARD:
		return C_JASON_DOWN;
	case JASON_STATE_DIRECTION_UPWARD:
		return C_JASON_UP;
	default:
		return C_JASON_HORIZON;
	}
}

void CJasonDirectionState::Stay()
{
	auto targetAnimations = this->target->GetAnimations();
	auto animation = targetAnimations.at(MappingStateOfAnimation(this->GetState()));
	animation->SetWait(true);
}

void CJasonDirectionState::MoveBackward()
{
	auto targetAnimations = this->target->GetAnimations();
	auto animation = targetAnimations.at(MappingStateOfAnimation(this->GetState()));

	animation->SetReverse(false);
	animation->SetWait(false);
}

void CJasonDirectionState::MoveForward()
{
	auto targetAnimations = this->target->GetAnimations();
	auto animation = targetAnimations.at(MappingStateOfAnimation(this->GetState()));

	animation->SetReverse(true);
	animation->SetWait(false);
}

void CJasonDirectionState::MoveUpward()
{
	auto targetAnimations = this->target->GetAnimations();
	auto animation = targetAnimations.at(MappingStateOfAnimation(this->GetState()));

	animation->SetReverse(false);
	animation->SetWait(false);
}

void CJasonDirectionState::MoveDownWard()
{
	auto targetAnimations = this->target->GetAnimations();
	auto animation = targetAnimations.at(MappingStateOfAnimation(this->GetState()));

	animation->SetReverse(false);
	animation->SetWait(false);
}
