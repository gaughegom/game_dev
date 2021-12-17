#include "SophiaGun.h"

constexpr auto SPR_GUN_00 = "gun00";
constexpr auto SPR_GUN_45 = "gun45";
constexpr auto SPR_GUN_90 = "gun90";

CSophiaGun::CSophiaGun()
{
}

CSophiaGun::CSophiaGun(CSophia* target)
{
	this->self = target;
	this->AddSprite(SPR_GUN_00, "sprSGun00");
	this->AddSprite(SPR_GUN_45, "sprSGun45");
	this->AddSprite(SPR_GUN_90, "sprSGun90");
}

void CSophiaGun::Update(DWORD dt)
{
}

void CSophiaGun::Render()
{
	D3DCOLOR color = self->GetSophiaPartRenderColor();
	std::string spriteId = this->MappingGunSpriteState(this->self->GetActionState());
	
	this->sprites.at(spriteId)->Draw(
		this->position + this->self->GetPosition(), 
		-this->self->GetNx(),
		color);
}

std::string CSophiaGun::MappingGunSpriteState(SophiaActionState actionState)
{
	switch (actionState)
	{
	case SophiaActionState::Idle:
		this->SetPosition(Vector2D(8.0f * this->self->GetNx(), 9.0f));
		return SPR_GUN_00; // gun_00
		break;
	case SophiaActionState::Tile45:
		this->SetPosition(Vector2D(8.0f * this->self->GetNx(), 21.0f));
		return SPR_GUN_45; // gun_45
		break;
	case SophiaActionState::Up90:
		this->SetPosition(Vector2D(3.0f * this->self->GetNx(), 24.0f));
		return SPR_GUN_90; // gun_90
		break;
	default:
		break;
	}
}