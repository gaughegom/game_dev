#include "SophiaActionState.h"

CSophiaActionState::CSophiaActionState()
{
}

CSophiaActionState::CSophiaActionState(CSophia* target)
{
	this->target = target;
}

void CSophiaActionState::SetTarget(CSophia* target)
{
	this->target = target;
}

void CSophiaActionState::IdleState()
{
	this->target->leftWheel = Vector2D(-8.0f, 0.0f);
	this->target->rightWheel = Vector2D(8.0f, 0.0f);
	this->target->body = Vector2D(0.0f, 1.0f);
	this->target->cabin = Vector2D(-3.5f * this->target->GetNx(), 9.0f);
	this->target->gun = Vector2D(8.0f * this->target->GetNx(), 9.0f);

	auto sprites = CSprites::GetInstance();
	this->target->lpsCabin = sprites->Get(SPRITE_SOPHIA_CABIN_00);
	this->target->lpsGun = sprites->Get(SPRITE_SOPHIA_GUN_00);
}

void CSophiaActionState::Tilt45State()
{
	this->target->leftWheel = Vector2D(-6.5f, 0.0f);
	this->target->rightWheel = Vector2D(6.5f, 0.0f);
	this->target->body = Vector2D(0.0f, 6.0f);
	this->target->cabin = Vector2D(-3.5f * this->target->GetNx(), 14.0f);
	this->target->gun = Vector2D(8.0f * this->target->GetNx(), 21.0f);

	auto sprites = CSprites::GetInstance();
	this->target->lpsCabin = sprites->Get(SPRITE_SOPHIA_CABIN_45);
	this->target->lpsGun = sprites->Get(SPRITE_SOPHIA_GUN_45);
}

void CSophiaActionState::Up90State()
{
	this->target->leftWheel = Vector2D(-5.0f, 0.0f);
	this->target->rightWheel = Vector2D(5.0f, 0.0f);
	this->target->body = Vector2D(0.0f, 7.0f);
	this->target->cabin = Vector2D(-7.0f * this->target->GetNx(), 13.0f);
	this->target->gun = Vector2D(-3.0f * this->target->GetNx(), 24.0f);

	auto sprites = CSprites::GetInstance();
	this->target->lpsCabin = sprites->Get(SPRITE_SOPHIA_CABIN_45);
	this->target->lpsGun = sprites->Get(SPRITE_SOPHIA_GUN_90);
}

void CSophiaActionState::SetState(int state)
{
	this->state = state;
}

int CSophiaActionState::GetState()
{
	return this->state;
}
