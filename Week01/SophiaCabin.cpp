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
		this->sophia->GetNx());
}

int CSophiaCabin::MappingCabinSpriteState(SophiaActionState actionState)
{
	switch (actionState)
	{
	case SophiaActionState::Idle:
		this->SetPosition(-3.5f * this->sophia->GetNx(), 9.0f);
		return SPRITE_SOPHIA_CABIN_00;

	case SophiaActionState::Tile45:
		this->SetPosition(-3.5f * this->sophia->GetNx(), 13.0f);
		return SPRITE_SOPHIA_CABIN_45;

	case SophiaActionState::Up90:
		this->SetPosition(-3.5f * this->sophia->GetNx(), 14.0f);
		return SPRITE_SOPHIA_CABIN_45;

	default:
		return SPRITE_SOPHIA_CABIN_00;
	}
}
