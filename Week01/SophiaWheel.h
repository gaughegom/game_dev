#pragma once
#ifndef _SOPHIA_WHEEL_H
#define _SOPHIA_WHEEL_H

#include "GameObject.h"
#include "GameMovement.h"

class CSophiaWheel : CGameObject {
public:
	void Update(DWORD dt);
	void Render();
};

#endif // !_SOPHIA_WHEEL_H
