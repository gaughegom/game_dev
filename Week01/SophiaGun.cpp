#include "SophiaGun.h"

constexpr auto SpriteGun00Id = "gun00";
constexpr auto SpriteGun45Id = "gun45";
constexpr auto SpriteGun90Id = "gun90";

CSophiaGun::CSophiaGun()
{
}

CSophiaGun::CSophiaGun(CSophia* target)
{
	this->self = target;
	this->AddSprite(SpriteGun00Id, "sprSGun00");
	this->AddSprite(SpriteGun45Id, "sprSGun45");
	this->AddSprite(SpriteGun90Id, "sprSGun90");
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
		return SpriteGun00Id; // gun_00
		break;
	case SophiaActionState::Tile45:
		this->SetPosition(Vector2D(8.0f * this->self->GetNx(), 21.0f));
		return SpriteGun45Id; // gun_45
		break;
	case SophiaActionState::Up90:
		this->SetPosition(Vector2D(3.0f * this->self->GetNx(), 24.0f));
		return SpriteGun90Id; // gun_90
		break;
	default:
		break;
	}
}