#include "SophiaBody.h"

CSophiaBody::CSophiaBody(CSophia* target)
{
	this->sophia = target;
}

void CSophiaBody::Update(DWORD dt)
{
}

void CSophiaBody::Render()
{
	auto sprite = CSprites::GetInstance()->Get(4); // 4: sophia body

	// handle animation action state
	this->HandleAnimationActionState(this->sophia->GetActionState());

	sprite->Draw(this->position + this->sophia->GetPosition(), 1);
}

void CSophiaBody::HandleAnimationActionState(SophiaActionState actionState)
{
	switch (actionState)
	{
	case SophiaActionState::Idle:
		this->SetPosition(0.0f, 1.0f);
		break;
	case SophiaActionState::Tile45:
		this->SetPosition(0.0f, 6.0f);
		break;
	case SophiaActionState::Up90:
		this->SetPosition(0.0f, 7.0f);
		break;
	default:
		break;
	}
}
