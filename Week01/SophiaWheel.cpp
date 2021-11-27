#include "SophiaWheel.h"

CSophiaWheel::CSophiaWheel(CSophia* target)
{
	this->sophia = target;
}

void CSophiaWheel::Update(DWORD dt)
{
}

void CSophiaWheel::Render()
{
	auto animation = this->animations.at(C_A_DEFAULT_KEY);

	this->HandleAnimationDirectState(this->sophia->GetDirectState());
	this->HandleAnimationActionState(this->sophia->GetActionState());

	animation->Render(
		this->position + this->sophia->GetPosition(), 
		this->sophia->GetNx());
}

// set prop in animation of wheel by target state
void CSophiaWheel::HandleAnimationDirectState(SophiaDirectState directState)
{
	switch (directState)
	{
	case SophiaDirectState::Stay:
		this->NotMove();
		break;

	case SophiaDirectState::RightMove:
		this->RightMove();
		break;

	case SophiaDirectState::LeftMove:
		this->LeftMove();
		break;

	default:
		this->NotMove();
		break;
	}
}

void CSophiaWheel::HandleAnimationActionState(SophiaActionState actionState)
{
	switch (actionState)
	{
	case SophiaActionState::Idle:
		this->sophia->GetLeftWheel()->SetPosition(-8.0f, 0.0f);
		this->sophia->GetRightWheel()->SetPosition(8.0f, 0.0f);
		break;
	case SophiaActionState::Tile45:
		this->sophia->GetLeftWheel()->SetPosition(-6.5f, 0.0f);
		this->sophia->GetRightWheel()->SetPosition(06.5f, 0.0f);
		break;
	case SophiaActionState::Up90:
		this->sophia->GetLeftWheel()->SetPosition(-5.0f, 0.0f);
		this->sophia->GetRightWheel()->SetPosition(5.0f, 0.0f);
		break;

	default:
		break;
	}
}

#pragma region SET ANIMATION PROP

void CSophiaWheel::NotMove()
{
	this->animations.at(C_A_DEFAULT_KEY)->SetWait(true);
}

void CSophiaWheel::RightMove()
{
	this->animations.at(C_A_DEFAULT_KEY)->SetWait(false);
	this->animations.at(C_A_DEFAULT_KEY)->SetReverse(true);
}

void CSophiaWheel::LeftMove()
{
	this->animations.at(C_A_DEFAULT_KEY)->SetWait(false);
	this->animations.at(C_A_DEFAULT_KEY)->SetReverse(true);
}

#pragma endregion