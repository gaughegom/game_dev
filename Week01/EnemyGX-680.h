#pragma once
#ifndef _ENEMY_GX680_H
#define _ENEMY_GX680_H

#include "GameObject.h"

#define C_GX680			0

class CEnemyGX680 : public CGameObject {
private:

public:
	CEnemyGX680();

	void Update(DWORD dt);
	void Render();
};

#endif // !_ENEMY_GX-680_H
