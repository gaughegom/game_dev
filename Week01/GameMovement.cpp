#include "GameMovement.h"

void LinearMoveWithGravity(CGameObject& object, DWORD dt)
{
	auto objectVelocity = object.GetVelocity();
	object.SetVelocity(objectVelocity.x, objectVelocity.y + (-PLAYER_GRAVITY * dt));
	
	auto x = object.GetX() + objectVelocity.x * dt;
	object.SetX(x);

	auto y = object.GetY() + objectVelocity.y * dt;
	object.SetY(y);

}

void LinearMove(CGameObject& object, DWORD dt)
{
	auto objectVelocity = object.GetVelocity();
	auto x = object.GetX() + objectVelocity.x * dt;
	object.SetX(x);
	auto y = object.GetY() + objectVelocity.y * dt;
	object.SetY(y);
}
