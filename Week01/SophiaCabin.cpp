#include "SophiaCabin.h"

CSophiaCabin::CSophiaCabin(CSophia* target)
{
	this->sophia = target;
}


void CSophiaCabin::Update(DWORD dt)
{
}

void CSophiaCabin::Render()
{
	// get sprite of sophia cabin
	int spriteId = this->MappingCabinSpriteState(this->sophia->GetActionState());
	auto sprite = CSprites::GetInstance()->Get(spriteId);

	sprite->Draw(
		this->position + this->sophia->GetPosition(), 
		-this->sophia->GetNx());
}

int CSophiaCabin::MappingCabinSpriteState(SophiaActionState actionState)
{
	switch (actionState)
	{
	case SophiaActionState::Idle:
		this->SetPosition(-3.5f * this->sophia->GetNx(), 9.0f);
		return 5; // cabin_00

	case SophiaActionState::Tile45:
		this->SetPosition(-3.5f * this->sophia->GetNx(), 13.0f);
		return 6; // cabin_45

	case SophiaActionState::Up90:
		this->SetPosition(-3.5f * this->sophia->GetNx(), 14.0f);
		return 6;

	default:
		return 5;
	}
}
