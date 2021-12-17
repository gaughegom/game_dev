#include "SophiaBody.h"

#define V_POSITION_IDLE		Vector2D(0.0f, 1.0f)
#define V_POSITION_TILE45	Vector2D(0.0f, 6.0f)
#define V_POSITION_UP90		Vector2D(0.0f, 7.0f)

constexpr auto SpriteBodyId = "df";

CSophiaBody::CSophiaBody(CSophia* target)
{
	this->self = target;
	this->AddSprite(SpriteBodyId, "sprSBody00");
}

void CSophiaBody::Update(DWORD dt)
{
}

void CSophiaBody::Render()
{
	D3DCOLOR color = self->GetSophiaPartRenderColor();
	auto sprite = this->sprites.at(SpriteBodyId);

	// handle animation action state
	this->HandleAnimationActionState(this->self->GetActionState());

	sprite->Draw(this->position + this->self->GetPosition(), -1, color);
}

void CSophiaBody::HandleAnimationActionState(SophiaActionState actionState)
{
	switch (actionState)
	{
	case SophiaActionState::Idle:
		this->SetPosition(V_POSITION_IDLE);
		break;
	case SophiaActionState::Tile45:
		this->SetPosition(V_POSITION_TILE45);
		break;
	case SophiaActionState::Up90:
		this->SetPosition(V_POSITION_UP90);
		break;
	default:
		break;
	}
}
