#pragma once
#ifndef _SIMULATION_ENVIROMENT_H
#define _SIMULATION_ENVIROMENT_H

#include "resources.h"
#include <math.h>
#include "GameObject.h"

class CGameObject;

void InGravityAffect(CGameObject* self, DWORD dt);

#endif // !_SIMULATION_ENVIROMENT_H
