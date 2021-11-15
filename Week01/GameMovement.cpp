#include "GameMovement.h"


void MoveLinear(Vector2D& vPosition, Vector2D& vVelocity, DWORD dt)
{
	vPosition += vVelocity * dt;
}
