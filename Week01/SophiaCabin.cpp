#include "SophiaCabin.h"

#define SPR_SOPHIA_CABIN_00		"cabin00"
#define SPR_SOPHIA_CABIN_45		"cabin45"
#define SPR_SOPHIA_CABIN_90		"cabin90"
#define SPR_SOPHIA_CABIN_IN		"cabinIn"
#define SPR_SOPHIA_CABIN_OUT	"cabinOut"

CSophiaCabin::CSophiaCabin(CSophia* target)
{
	this->self = target;
	this->AddSprite(SPR_SOPHIA_CABIN_00, "sprSCabin00");
	this->AddSprite(SPR_SOPHIA_CABIN_45, "sprSCabin45");
	this->AddSprite(SPR_SOPHIA_CABIN_90, "sprSCabin90");
	this->AddSprite(SPR_SOPHIA_CABIN_IN, "sprSCabinIn");
	this->AddSprite(SPR_SOPHIA_CABIN_OUT, "sprSCabinOut");
}

void CSophiaCabin::Update(DWORD dt)
{
}

void CSophiaCabin::Render()
{
	// get sprite of self cabin
	std::string spriteId = this->MappingCabinSpriteState(this->self->GetActionState());
	auto sprite = this->sprites.at(spriteId);

sprite->Draw(
		this->position + this->self->GetPosition(), 
		-this->self->GetNx(),
		DRAW_COLOR_DEFAULT);
}

std::string CSophiaCabin::MappingCabinSpriteState(SophiaActionState actionState)
{
	switch (actionState)
	{
	case SophiaActionState::Idle:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 9.0f));
		return SPR_SOPHIA_CABIN_00; // cabin_00

	case SophiaActionState::Tile45:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 13.0f));
		return SPR_SOPHIA_CABIN_45; // cabin_45

	case SophiaActionState::Up90:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 14.0f));
		return SPR_SOPHIA_CABIN_45;

	case SophiaActionState::OpenIn:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 9.0f));
		return SPR_SOPHIA_CABIN_IN;

	case SophiaActionState::OpenOut:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 9.0f));
		return SPR_SOPHIA_CABIN_OUT;

	default:
		return SPR_SOPHIA_CABIN_00;
	}
}
