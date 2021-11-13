#include "GameMovement.h"
#include <math.h>

void Move_rectilinear(CVector2D& vPosition, CVector2D& vVelocity, DWORD dt)
{
	vPosition += vVelocity * dt;
}
