#include "GameMovement.h"


void LinearMovement(Vector2D& vPosition, Vector2D& vVelocity, DWORD dt)
{
	vPosition += vVelocity * dt;
}
