#include "GameMovement.h"


void Move_rectilinear(Vector2D& vPosition, Vector2D& vVelocity, DWORD dt)
{
	vPosition += vVelocity * dt;
}
