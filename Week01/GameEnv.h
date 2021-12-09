#pragma once
#ifndef _GAME_ENV_H
#define _GAME_ENV_H

#include "resources.h"
#include <math.h>
#include "GameObject.h"

class CGameObject;

void InGravityAffect(CGameObject* self, DWORD dt);
void InHorizontalMove(CGameObject* self, DWORD dt);
void InSinWave(CGameObject* self, DWORD dt, float amplitude);

#endif // !_GAME_ENV_H
