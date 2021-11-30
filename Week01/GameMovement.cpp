#include "GameMovement.h"

void LinearMove(CGameObject* target, DWORD dt)
{
	Vector2D position = target->GetPosition();
	Vector2D velocity = target->GetVelocity();
	position += velocity * dt;
	target->SetPosition(position);
}

void LinearMoveInGravity(CGameObject* target, DWORD dt)
{
	Vector2D position = target->GetPosition();
	Vector2D velocity = target->GetVelocity();

	position += velocity * dt;
	target->SetPosition(position);
	velocity.y += -PLAYER_GRAVITY;
	target->SetVelocity(velocity);
}
