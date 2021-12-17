#include "SophiaCabin.h"

constexpr auto SpriteCabin00Id = "cabin00";
constexpr auto SpriteCabin45Id = "cabin45";
constexpr auto SpriteCabin90Id = "cabin90";
constexpr auto SpriteCabinInId = "cabinIn";
constexpr auto SpriteCabinOutId = "cabinOut";

CSophiaCabin::CSophiaCabin(CSophia* target)
{
	this->self = target;
	this->AddSprite(SpriteCabin00Id, "sprSCabin00");
	this->AddSprite(SpriteCabin45Id, "sprSCabin45");
	this->AddSprite(SpriteCabin90Id, "sprSCabin90");
	this->AddSprite(SpriteCabinInId, "sprSCabinIn");
	this->AddSprite(SpriteCabinOutId, "sprSCabinOut");
}

void CSophiaCabin::Update(DWORD dt)
{
}

void CSophiaCabin::Render()
{
	D3DCOLOR color = self->GetSophiaPartRenderColor();

	// get sprite of self cabin
	std::string spriteId = this->MappingCabinSpriteState(this->self->GetActionState());
	auto sprite = this->sprites.at(spriteId);

	sprite->Draw(
		this->position + this->self->GetPosition(), 
		-this->self->GetNx(),
		color);
}

std::string CSophiaCabin::MappingCabinSpriteState(SophiaActionState actionState)
{
	switch (actionState)
	{
	case SophiaActionState::Idle:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 9.0f));
		return SpriteCabin00Id; // cabin_00

	case SophiaActionState::Tile45:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 13.0f));
		return SpriteCabin45Id; // cabin_45

	case SophiaActionState::Up90:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 14.0f));
		return SpriteCabin45Id;

	case SophiaActionState::OpenIn:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 9.0f));
		return SpriteCabinInId;

	case SophiaActionState::OpenOut:
		this->SetPosition(Vector2D(-3.5f * this->self->GetNx(), 9.0f));
		return SpriteCabinOutId;

	default:
		return SpriteCabin00Id;
	}
}
