#include "GameMovement.h"

void LinearMoveWithGravity(CGameObject& object, DWORD dt)
{
	auto objectVelocity = object.GetVelocity();
	auto x = object.GetX() + objectVelocity.x * dt;
	object.SetX(x);

	auto y = object.GetY() + objectVelocity.y * dt;
	object.SetY(y);

	object.SetVelocity(objectVelocity.x, objectVelocity.y + (-PLAYER_GRAVITY * dt));
}

void LinearMove(CGameObject& object, DWORD dt)
{
	auto objectVelocity = object.GetVelocity();
	auto x = object.GetX() + objectVelocity.x * dt;
	object.SetX(x);
	auto y = object.GetY() + objectVelocity.y * dt;
	object.SetY(y);
}
