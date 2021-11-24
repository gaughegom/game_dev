#pragma once
#ifndef _GAMEMOVEMENT_H
#define _GAMEMOVEMENT_H

#include "resources.h"
#include <math.h>
#include "GameObject.h"

class CGameObject;

void LinearMove(CGameObject* target, DWORD dt);
void LinearMoveInGravity(CGameObject* target, DWORD dt);

#endif // !_GAMEMOVEMENT_H
