#pragma once
#ifndef _GAME_ENV_H
#define _GAME_ENV_H

#include "resources.h"
#include <math.h>
#include "GameObject.h"

class CGameObject;

void InGravityAffect(CGameObject* self, DWORD dt);
void InHorizontalMove(CGameObject* self, DWORD dt);
void InSinWaveXAsix(CGameObject* self, DWORD dt, float frequecy, float amplitude);
void InSinWaveYAsix(CGameObject* self, DWORD dt, float frequecy, float amplitude);

int RandomDirect();
int Random(int begin, int end);


#endif // !_GAME_ENV_H
