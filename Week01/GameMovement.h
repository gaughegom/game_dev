#pragma once
#ifndef _GAMEMOVEMENT_H
#define _GAMEMOVEMENT_H

#include "Vector2D.h"

void Move_rectilinear(CVector2D& vCurPosition, CVector2D& vCurVelocity, DWORD dt);
void Move_parabol(CVector2D& vCurPosition, CVector2D& vCurVelocity, DWORD dt);

#endif // !_GAMEMOVEMENT_H
