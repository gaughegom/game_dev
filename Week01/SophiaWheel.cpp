#include "SophiaWheel.h"

CSophiaWheel::CSophiaWheel(CSophia* target)
{
	this->self = target;
}

void CSophiaWheel::Update(DWORD dt)
{
}

void CSophiaWheel::Render()
{
	auto animation = this->animations.at(C_A_DEFAULT_KEY);

	this->HandleAnimationDirectState();
	this->HandleAnimationActionState();

	animation->Render(
		this->position + this->self->GetPosition(), 
		-this->self->GetNx(),
		255);
}

// set prop in animation of wheel by target state
void CSophiaWheel::HandleAnimationDirectState()
{
	switch (this->self->GetDirectState())
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

void CSophiaWheel::HandleAnimationActionState()
{
	switch (this->self->GetActionState())
	{
	case SophiaActionState::Idle:
		this->self->GetLeftWheel()->SetPosition(V_LEFT_POSITION_IDLE);
		this->self->GetRightWheel()->SetPosition(V_RIGHT_POSITION_IDLE);
		break;
	case SophiaActionState::Tile45:
		this->self->GetLeftWheel()->SetPosition(V_LEFT_POSITION_TILE45);
		this->self->GetRightWheel()->SetPosition(V_RIGHT_POSITION_TILE45);
		break;
	case SophiaActionState::Up90:
		this->self->GetLeftWheel()->SetPosition(V_LEFT_POSITION_UP90);
		this->self->GetRightWheel()->SetPosition(V_RIGHT_POSITION_UP90);
		break;

	default:
		break;
	}
}

#pragma region SET ANIMATION PROP

void CSophiaWheel::NotMove()
{
	this->animations.at(C_A_DEFAULT_KEY)->SetWait(true);
	this->animations.at(C_A_DEFAULT_KEY)->SetReverse(false);
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