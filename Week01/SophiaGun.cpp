#include "SophiaGun.h"

CSophiaGun::CSophiaGun()
{
}

CSophiaGun::CSophiaGun(CSophia* target)
{
	this->self = target;
}

void CSophiaGun::Update(DWORD dt)
{
}

void CSophiaGun::Render()
{
	auto spriteId = this->MappingGunSpriteState(this->self->GetActionState());
	auto sprites = CSprites::GetInstance();
	sprites->Get(spriteId)->Draw(
		this->position + this->self->GetPosition(), 
		-this->self->GetNx(),
		DRAW_COLOR_DEFAULT);
}

int CSophiaGun::MappingGunSpriteState(SophiaActionState actionState)
{
	switch (actionState)
	{
	case SophiaActionState::Idle:
		this->SetPosition(Vector2D(8.0f * this->self->GetNx(), 9.0f));
		return 10; // gun_00
		break;
	case SophiaActionState::Tile45:
		this->SetPosition(Vector2D(8.0f * this->self->GetNx(), 21.0f));
		return 11; // gun_45
		break;
	case SophiaActionState::Up90:
		this->SetPosition(Vector2D(3.0f * this->self->GetNx(), 24.0f));
		return 12; // gun_90
		break;
	default:
		break;
	}
}