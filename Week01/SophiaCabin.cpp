#include "SophiaCabin.h"

CSophiaCabin::CSophiaCabin(CSophia* target)
{
	this->self = target;
}

void CSophiaCabin::Update(DWORD dt)
{
}

void CSophiaCabin::Render()
{
	// get sprite of self cabin
	int spriteId = this->MappingCabinSpriteState(this->self->GetActionState());
	auto sprite = CSprites::GetInstance()->Get(spriteId);

	sprite->Draw(
		this->position + this->self->GetPosition(), 
		-this->self->GetNx(),
		255);
}

int CSophiaCabin::MappingCabinSpriteState(SophiaActionState actionState)
{
	switch (actionState)
	{
	case SophiaActionState::Idle:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 9.0f));
		return 5; // cabin_00

	case SophiaActionState::Tile45:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 13.0f));
		return 6; // cabin_45

	case SophiaActionState::Up90:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 14.0f));
		return 6;

	case SophiaActionState::OpenIn:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 9.0f));
		return 8;

	case SophiaActionState::OpenOut:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 9.0f));
		return 9;

	default:
		return 5;
	}
}
