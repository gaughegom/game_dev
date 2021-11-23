#pragma once
#ifndef _GAMEMOVEMENT_H
#define _GAMEMOVEMENT_H

#include "resources.h"
#include <math.h>
#include "GameObject.h"

class CGameObject;

void LinearMoveWithGravity(CGameObject& object, DWORD dt);
void LinearMove(CGameObject& object, DWORD dt);

#endif // !_GAMEMOVEMENT_H
