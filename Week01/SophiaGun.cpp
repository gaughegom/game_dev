#include "SophiaGun.h"

CSophiaGun::CSophiaGun()
{
}

CSophiaGun::CSophiaGun(CSophia* target)
{
	this->sophia = target;
}

void CSophiaGun::Update(DWORD dt)
{
}

void CSophiaGun::Render()
{
	auto spriteId = this->MappingGunSpriteState(this->sophia->GetActionState());
	auto sprites = CSprites::GetInstance();
	sprites->Get(spriteId)->Draw(
		this->position + this->sophia->GetPosition(), 
		this->sophia->GetNx());
}



int CSophiaGun::MappingGunSpriteState(SophiaActionState actionState)
{
	switch (actionState)
	{
	case SophiaActionState::Idle:
		this->SetPosition(8.0f * this->sophia->GetNx(), 9.0f);
		return 8; // gun_00
		break;
	case SophiaActionState::Tile45:
		this->SetPosition(8.0f * this->sophia->GetNx(), 21.0f);
		return 9; // gun_45
		break;
	case SophiaActionState::Up90:
		this->SetPosition(3.0f * this->sophia->GetNx(), 24.0f);
		return 10; // gun_90
		break;
	default:
		break;
	}
}