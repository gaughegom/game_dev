#pragma once
#ifndef _ENEMY_GX680_H
#define _ENEMY_GX680_H

#include "EnemyBase.h"

#define C_GX680			0

class CEnemyGX680 : public CEnemyBase {
private:

public:
	CEnemyGX680();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_ENEMY_GX-680_H
