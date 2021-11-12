#include "GameMovement.h"
#include <math.h>

void Move_rectilinear(CVector2D& vCurPosition, CVector2D& vCurVelocity, DWORD dt)
{
	vCurPosition += vCurVelocity * dt;
}

void Move_parabol(CVector2D& vCurPosition, CVector2D& vCurVelocity, DWORD dt)
{
	vCurPosition.x += vCurVelocity.x / sqrt(2);
	vCurPosition.y += -(10 / 2) * pow(dt, 2) + vCurPosition.x * dt / sqrt(2);
}
